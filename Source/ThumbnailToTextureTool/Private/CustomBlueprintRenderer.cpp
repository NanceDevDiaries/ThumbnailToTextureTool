// Credits please, open source from NanceDevDiaries. Game on!

#include "CustomBlueprintRenderer.h"

#include "CustomThumbnailHelpers.h"
#include "IThumbnailToTextureTool.h"
#include "ThumbnailToTextureSettings.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "ThumbnailRendering/ThumbnailManager.h"

UCustomBlueprintRenderer::UCustomBlueprintRenderer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FKismetEditorUtilities::OnBlueprintUnloaded.AddUObject(this, &UCustomBlueprintRenderer::OnBlueprintUnloaded);
}


void UCustomBlueprintRenderer::Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height,
                                                FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily)
{
	UBlueprint* Blueprint = Cast<UBlueprint>(Object);

	// Strict validation - it may hopefully fix UE-35705.
	const bool bIsBlueprintValid = IsValid(Blueprint)
		&& IsValid(Blueprint->GeneratedClass)
		&& Blueprint->bHasBeenRegenerated
		//&& Blueprint->IsUpToDate() - This condition makes the thumbnail blank whenever the BP is dirty. It seems too strict.
		&& !Blueprint->bBeingCompiled
		&& !Blueprint->HasAnyFlags(RF_Transient);
	if (bIsBlueprintValid)
	{
		TSharedRef<FCustomBlueprintThumbnailScene> ThumbnailScene = CustomThumbnailScenes.EnsureThumbnailScene(Blueprint->GeneratedClass);

		ThumbnailScene->SetBlueprint(Blueprint);
		IThumbnailToTextureToolModule& Module = FModuleManager::GetModuleChecked<IThumbnailToTextureToolModule>("ThumbnailToTextureTool");

		const bool IsTransparent = Module.GetEditorSettings().UseTransparentBackground;
		UMaterial* MaterialInstance = Cast<UMaterial>( Module.GetEditorSettings().GetBackgroundMaterial());
		ThumbnailScene->SetMaterial(MaterialInstance, IsTransparent);
		
		FSceneViewFamilyContext ViewFamily( FSceneViewFamily::ConstructionValues( RenderTarget, ThumbnailScene->GetScene(), FEngineShowFlags(ESFIM_Game) )
			.SetTime(UThumbnailRenderer::GetTime())
			.SetAdditionalViewFamily(bAdditionalViewFamily));

		ViewFamily.EngineShowFlags.DisableAdvancedFeatures();
		ViewFamily.EngineShowFlags.LOD = 0;

		RenderViewFamily(Canvas, &ViewFamily, ThumbnailScene->CreateView(&ViewFamily, X, Y, Width, Height));
	}
}

bool UCustomBlueprintRenderer::CanVisualizeAsset(UObject* Object)
{
	UBlueprint* Blueprint = Cast<UBlueprint>(Object);

	bool bCanVisualizeAsset = false;

	// Only visualize actor based blueprints
	if (Blueprint && Blueprint->GeneratedClass && Blueprint->GeneratedClass->IsChildOf(AActor::StaticClass()))
	{
		AActor::ForEachComponentOfActorClassDefault<UActorComponent>(TSubclassOf<AActor>(Blueprint->GeneratedClass), [&](const UActorComponent* Component)
		{
			bCanVisualizeAsset = FBlueprintThumbnailScene::IsValidComponentForVisualization(Component);
			return !bCanVisualizeAsset;
		});
	}

	return bCanVisualizeAsset;
}

void UCustomBlueprintRenderer::BeginDestroy()
{
	FKismetEditorUtilities::OnBlueprintUnloaded.RemoveAll(this);
	CustomThumbnailScenes.Clear();

	Super::BeginDestroy();
}

void UCustomBlueprintRenderer::BlueprintChanged(UBlueprint* Blueprint)
{
	if (Blueprint && Blueprint->GeneratedClass)
	{
		TSharedPtr<FCustomBlueprintThumbnailScene> ThumbnailScene = CustomThumbnailScenes.FindThumbnailScene(Blueprint->GeneratedClass);
		if (ThumbnailScene.IsValid())
		{
			ThumbnailScene->BlueprintChanged(Blueprint);
		}
	}
}

void UCustomBlueprintRenderer::OnBlueprintUnloaded(UBlueprint* Blueprint)
{
	if (Blueprint && Blueprint->GeneratedClass)
	{
		CustomThumbnailScenes.RemoveThumbnailScene(Blueprint->GeneratedClass);
	}
}
