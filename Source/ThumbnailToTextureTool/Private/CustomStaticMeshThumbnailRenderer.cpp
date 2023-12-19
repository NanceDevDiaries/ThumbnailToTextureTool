// Credits please, open source from NanceDevDiaries. Game on!

#include "CustomStaticMeshThumbnailRenderer.h"

#include "CustomThumbnailHelpers.h"
#include "IThumbnailToTextureTool.h"
#include "Misc/App.h"
#include "ShowFlags.h"
#include "SceneInterface.h"
#include "SceneView.h"
#include "ThumbnailToTextureSettings.h"
#include "Engine/StaticMesh.h"

UCustomStaticMeshThumbnailRenderer::UCustomStaticMeshThumbnailRenderer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ThumbnailScene = nullptr;
}

void UCustomStaticMeshThumbnailRenderer::Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily)
{
	UStaticMesh* StaticMesh = Cast<UStaticMesh>(Object);
	if (IsValid(StaticMesh))
	{
		if (ThumbnailScene == nullptr || ensure(ThumbnailScene->GetWorld() != nullptr) == false)
		{
			if (ThumbnailScene)
			{
				FlushRenderingCommands();
				delete ThumbnailScene;
			}
			ThumbnailScene = new FCustomStaticMeshThumbnailScene();
		}

		ThumbnailScene->SetStaticMesh(StaticMesh);
		ThumbnailScene->GetScene()->UpdateSpeedTreeWind(0.0);

		FSceneViewFamilyContext ViewFamily( FSceneViewFamily::ConstructionValues( RenderTarget, ThumbnailScene->GetScene(), FEngineShowFlags(ESFIM_Game) )
			.SetTime(UThumbnailRenderer::GetTime())
			.SetAdditionalViewFamily(bAdditionalViewFamily));

		ViewFamily.EngineShowFlags.DisableAdvancedFeatures();
		ViewFamily.EngineShowFlags.MotionBlur = 0;
		ViewFamily.EngineShowFlags.LOD = 0;

		IThumbnailToTextureToolModule& Module = FModuleManager::GetModuleChecked<IThumbnailToTextureToolModule>("ThumbnailToTextureTool");

		const bool IsTransparent = Module.GetEditorSettings().UseTransparentBackground;
		UMaterial* MaterialInstance = Cast<UMaterial>( Module.GetEditorSettings().GetBackgroundMaterial());
		ThumbnailScene->SetMaterial(MaterialInstance, IsTransparent);
		
		RenderViewFamily(Canvas, &ViewFamily, ThumbnailScene->CreateView(&ViewFamily, X, Y, Width, Height));
		ThumbnailScene->SetStaticMesh(nullptr);
	}
}

void UCustomStaticMeshThumbnailRenderer::BeginDestroy()
{
	if ( ThumbnailScene != nullptr )
	{
		delete ThumbnailScene;
		ThumbnailScene = nullptr;
	}

	Super::BeginDestroy();
}
