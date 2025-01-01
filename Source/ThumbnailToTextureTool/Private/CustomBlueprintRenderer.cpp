// Credits please, open source from NanceDevDiaries. Game on!

#include "CustomBlueprintRenderer.h"

#include "CustomThumbnailHelpers.h"
#include "IThumbnailToTextureTool.h"
#include "ThumbnailToTextureSettings.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "ThumbnailRendering/ThumbnailManager.h"
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION <= 2
#include "Engine/Blueprint.h"
#include "Engine/SCS_Node.h"
#include "Engine/InheritableComponentHandler.h"
#endif

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
		ViewFamily.EngineShowFlags.MotionBlur = 0;
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
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION <= 2
		// Try to find any visible primitive components in the native class' CDO
		AActor* CDO = Blueprint->GeneratedClass->GetDefaultObject<AActor>();

		for (UActorComponent* Component : CDO->GetComponents())
		{
			if (FBlueprintThumbnailScene::IsValidComponentForVisualization(Component))
			{
				return true;
			}
		}

		UBlueprint* BlueprintToHarvestComponents = Blueprint;
		TSet<UBlueprint*> AllVisitedBlueprints;
		while (BlueprintToHarvestComponents)
		{
			AllVisitedBlueprints.Add(BlueprintToHarvestComponents);

			// Try to find any visible primitive components in the simple construction script
			if (BlueprintToHarvestComponents->SimpleConstructionScript)
			{
				for (USCS_Node* Node : BlueprintToHarvestComponents->SimpleConstructionScript->GetAllNodes())
				{
					if (FBlueprintThumbnailScene::IsValidComponentForVisualization(Node->ComponentTemplate))
					{
						return true;
					}
				}
			}

			// Check if any inheritable components from parents have valid data
			if (BlueprintToHarvestComponents->InheritableComponentHandler)
			{
				for (TArray<FComponentOverrideRecord>::TIterator InheritedComponentsIter = BlueprintToHarvestComponents->InheritableComponentHandler->CreateRecordIterator(); InheritedComponentsIter; ++InheritedComponentsIter)
				{
					if (FBlueprintThumbnailScene::IsValidComponentForVisualization(InheritedComponentsIter->ComponentTemplate))
					{
						return true;
					}
				}
			}

			UClass* ParentClass = BlueprintToHarvestComponents->ParentClass;
			BlueprintToHarvestComponents = nullptr;

			// If the parent class was a blueprint generated class, check it's simple construction script components as well
			if (ParentClass)
			{
				UBlueprint* ParentBlueprint = Cast<UBlueprint>(ParentClass->ClassGeneratedBy);

				// Also make sure we haven't visited the blueprint already. This would only happen if there was a loop of parent classes.
				if (ParentBlueprint && !AllVisitedBlueprints.Contains(ParentBlueprint))
				{
					BlueprintToHarvestComponents = ParentBlueprint;
				}
			}
		}
#else
		AActor::ForEachComponentOfActorClassDefault<UActorComponent>(TSubclassOf<AActor>(Blueprint->GeneratedClass), [&](const UActorComponent* Component)
			{
				bCanVisualizeAsset = FBlueprintThumbnailScene::IsValidComponentForVisualization(Component);
				return !bCanVisualizeAsset;
			});
#endif
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
