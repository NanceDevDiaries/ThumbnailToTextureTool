// Credits please, open source from NanceDevDiaries. Game on!

#include "IThumbnailToTextureTool.h"

#include "ContentBrowserModule.h"
#include "FileHelpers.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ObjectTools.h"
#include "ThumbnailToTextureSettings.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"

#define LOCTEXT_NAMESPACE "FThumbnailToTextureToolModule"

/**
 * Implements the FThumbnailToTextureToolModule module.
 */
class FThumbnailToTextureToolModule
	: public IThumbnailToTextureToolModule
{
public:
	FThumbnailToTextureToolModule();

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
	virtual UThumbnailToTextureSettings* GetEditorSettingsInstance() const override;

private:
	void AddContentBrowserContextMenuExtender();
	void RemoveContentBrowserContextMenuExtender();

	static TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& SelectedAssets);
	static void ExecuteSaveThumbnailAsTexture(FMenuBuilder& MenuBuilder, const TArray<FAssetData> SelectedAssets);

	FDelegateHandle ContentBrowserExtenderDelegateHandle;

	void CreateThumbnailSettings();
	UThumbnailToTextureSettings* ThumbnailToTextureEditorSettings;
};


FThumbnailToTextureToolModule::FThumbnailToTextureToolModule()
{
	ThumbnailToTextureEditorSettings = nullptr;
}

void FThumbnailToTextureToolModule::StartupModule()
{
	CreateThumbnailSettings();
	AddContentBrowserContextMenuExtender();
}

void FThumbnailToTextureToolModule::ShutdownModule()
{
	RemoveContentBrowserContextMenuExtender();

	// Unregister settings
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "TextureToTextureTool");
	}

	if (!GExitPurge) // If GExitPurge Object is already gone
	{
		ThumbnailToTextureEditorSettings->RemoveFromRoot();
	}
	ThumbnailToTextureEditorSettings = nullptr;
}

UThumbnailToTextureSettings* FThumbnailToTextureToolModule::GetEditorSettingsInstance() const
{
	return ThumbnailToTextureEditorSettings;
}

void FThumbnailToTextureToolModule::AddContentBrowserContextMenuExtender()
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(
		"ContentBrowser");
	TArray<FContentBrowserMenuExtender_SelectedAssets>& CBMenuExtenderDelegates = ContentBrowserModule.
		GetAllAssetViewContextMenuExtenders();

	CBMenuExtenderDelegates.Add(
		FContentBrowserMenuExtender_SelectedAssets::CreateStatic(
			&FThumbnailToTextureToolModule::OnExtendContentBrowserAssetSelectionMenu));
	ContentBrowserExtenderDelegateHandle = CBMenuExtenderDelegates.Last().GetHandle();
}

void FThumbnailToTextureToolModule::RemoveContentBrowserContextMenuExtender()
{
	if (ContentBrowserExtenderDelegateHandle.IsValid() && FModuleManager::Get().IsModuleLoaded("ContentBrowser"))
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::GetModuleChecked<FContentBrowserModule>(
			"ContentBrowser");
		TArray<FContentBrowserMenuExtender_SelectedAssets>& CBMenuExtenderDelegates = ContentBrowserModule.
			GetAllAssetViewContextMenuExtenders();
		CBMenuExtenderDelegates.RemoveAll([this](const FContentBrowserMenuExtender_SelectedAssets& Delegate)
		{
			return Delegate.GetHandle() == ContentBrowserExtenderDelegateHandle;
		});
	}
}

TSharedRef<FExtender> FThumbnailToTextureToolModule::OnExtendContentBrowserAssetSelectionMenu(
	const TArray<FAssetData>& SelectedAssets)
{
	TSharedRef<FExtender> Extender = MakeShared<FExtender>();

	// #todo filter out to only have assets that have a thumbnail already (Actors, not dataTables/dataAssets etc)

	Extender = MakeShared<FExtender>();
	Extender->AddMenuExtension(
		"CommonAssetActions",
		EExtensionHook::After,
		nullptr,
		FMenuExtensionDelegate::CreateStatic(&ExecuteSaveThumbnailAsTexture, SelectedAssets)
	);

	return Extender;
}

void FThumbnailToTextureToolModule::ExecuteSaveThumbnailAsTexture(FMenuBuilder& MenuBuilder,
                                                                  const TArray<FAssetData> SelectedAssets)
{
	// developed from engine code and help from a mix of https://forums.unrealengine.com/t/copy-asset-thumbnail-to-new-texture2d/138054/4
	// and https://isaratech.com/save-a-procedurally-generated-texture-as-a-new-asset/
	// and https://arrowinmyknee.com/2020/08/28/asset-right-click-menu-in-ue4/
	// and https://dev.epicgames.com/community/snippets/lw1/procedural-texture-with-c
	// and https://forums.unrealengine.com/t/programatically-created-asset-fails-to-save-or-crashes-the-editor/724517
	MenuBuilder.BeginSection("CreateTextureOffThumbnail", LOCTEXT("CreateTextureOffThumbnailMenuHeading", "Thumbnail"));
	{
		// Add Menu Entry Here
		MenuBuilder.AddMenuEntry(
			LOCTEXT("Thumbnail_NewTexture", "Export to Texture"),
			LOCTEXT("Thumbnail_NewTextureTooltip",
			        "Will export asset's thumbnail and put it in a folder defined in the project settings"),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateLambda([SelectedAssets]()
			{
				for (const FAssetData& AssetData : SelectedAssets)
				{
					FString GamePath = AssetData.GetAsset()->GetPathName();
					FString AssetName;
					if (int32 PathEnd; GamePath.FindLastChar('/', PathEnd))
					{
						++PathEnd;
						AssetName += GamePath;
						AssetName.RightChopInline(PathEnd);
						int32 extensionIdx;
						if (AssetName.FindChar('.', extensionIdx))
						{
							AssetName.LeftInline(extensionIdx);
						}
						GamePath.LeftInline(PathEnd);
						FString Prefix = GetEditorSettings().ThumbnailPrefix;
						FString NameWithPrefix = Prefix + AssetName;
						AssetName = NameWithPrefix;
					}
					else
					{
						AssetName = "T_Thumbnail";
					}

					if (int32 PathSeparatorIdx; AssetName.FindChar('/', PathSeparatorIdx))
					{
						// TextureName should not have any path separators in it
						return;
					}

					// Create the new texture 2D and save it on disk
					FString PackageFilename;
					const FName ObjectFullName = FName(*AssetData.GetFullName());
					TSet<FName> ObjectFullNames;
					ObjectFullNames.Add(ObjectFullName);

					FString PackageName = GetEditorSettings().RootTexture2DSaveDir.Path;
					if (!PackageName.EndsWith("/"))
					{
						PackageName += "/";
					}
					PackageName += AssetName;

					UPackage* Package = CreatePackage(*PackageName);
					Package->FullyLoad();

					UTexture2D* NewTexture = NewObject<UTexture2D>(Package, *AssetName,
					                                               RF_Public | RF_Standalone | RF_MarkAsRootSet);
					NewTexture->AddToRoot();

					// Load the image from the asset's loaded Thumbnail
					if (FPackageName::DoesPackageExist(AssetData.PackageName.ToString(), &PackageFilename))
					{
						FThumbnailMap ThumbnailMap;
						ThumbnailTools::LoadThumbnailsFromPackage(PackageFilename, ObjectFullNames,
						                                          ThumbnailMap);

						FObjectThumbnail* ObjectThumbnail = ThumbnailMap.Find(ObjectFullName);

						if (!ObjectThumbnail)
						{
							return;
						}

						int32 SizeX = ObjectThumbnail->GetImageWidth();
						int32 SizeY = ObjectThumbnail->GetImageHeight();
						
						FTexturePlatformData* platformData = new FTexturePlatformData();
						platformData->SizeX = SizeX;
						platformData->SizeY = SizeY;
						platformData->SetNumSlices(1);
						platformData->PixelFormat = PF_B8G8R8A8;
						NewTexture->SetPlatformData(platformData);
						NewTexture->MipGenSettings = TMGS_NoMipmaps;
						
						// similar to UTexture2D::CreateTransient but we're not creating a transient texture
						// Allocate first mipmap.
						int32 NumBlocksX = ObjectThumbnail->GetImageWidth() / GPixelFormats[PF_B8G8R8A8].BlockSizeX;
						int32 NumBlocksY = ObjectThumbnail->GetImageHeight() / GPixelFormats[PF_B8G8R8A8].BlockSizeY;
						FTexture2DMipMap* Mip = new FTexture2DMipMap(SizeX, SizeY, 1);
						NewTexture->GetPlatformData()->Mips.Add(Mip);
						Mip->BulkData.Lock(LOCK_READ_WRITE);
						Mip->BulkData.Realloc((int64)NumBlocksX * NumBlocksY * GPixelFormats[PF_B8G8R8A8].BlockBytes);
						Mip->BulkData.Unlock();

						// Apply Texture changes to GPU memory
						NewTexture->UpdateResource();

						NewTexture->Source.Init(SizeX, SizeY, 1,
						                        1,
						                        TSF_BGRA8, ObjectThumbnail->GetUncompressedImageData().GetData());
						NewTexture->LODGroup = TEXTUREGROUP_UI; // Prepare the asset for UI use
						NewTexture->CompressionSettings = TC_Default; // No need for "UserInterface2D", no need for alpha, it was also having issues making the asset have a thumbnail itself
						NewTexture->NeverStream = true;
						NewTexture->CompressionNoAlpha = true;

						NewTexture->UpdateResource();
						Package->FullyLoad();
						Package->SetDirtyFlag(true);
						FEditorFileUtils::PromptForCheckoutAndSave({Package},false,false);
						FAssetRegistryModule::AssetCreated(NewTexture);
					}
				}
			})),
			NAME_None,
			EUserInterfaceActionType::Button);
	}
	MenuBuilder.EndSection();
}

void FThumbnailToTextureToolModule::CreateThumbnailSettings()
{
	ThumbnailToTextureEditorSettings = NewObject<UThumbnailToTextureSettings>(
		GetTransientPackage(), UThumbnailToTextureSettings::StaticClass());
	check(ThumbnailToTextureEditorSettings);
	ThumbnailToTextureEditorSettings->AddToRoot();

	// Register settings
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		ISettingsSectionPtr EditorSettingsSection = SettingsModule->RegisterSettings(
			"Project", "Plugins", "TextureToTextureEditor",
			NSLOCTEXT("ThumbnailToTextureTool", "ThumbnailToTextureSettingsName",
			          "Thumbnail To Texture Editor defaults"),
			NSLOCTEXT("ThumbnailToTextureTool", "ThumbnailToTextureSettingsDescription",
			          "Configure Thumbnail To Texture Editor defaults."),
			ThumbnailToTextureEditorSettings);
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FThumbnailToTextureToolModule, ThumbnailToTextureTool)
