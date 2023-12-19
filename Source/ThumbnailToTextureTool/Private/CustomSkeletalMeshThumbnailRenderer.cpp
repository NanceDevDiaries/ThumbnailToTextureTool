// Credits please, open source from NanceDevDiaries. Game on!


#include "CustomSkeletalMeshThumbnailRenderer.h"

#include "CustomThumbnailHelpers.h"
#include "IThumbnailToTextureTool.h"
#include "ThumbnailRendering/SkeletalMeshThumbnailRenderer.h"
#include "Misc/App.h"
#include "ShowFlags.h"
#include "SceneView.h"
#include "Engine/SkeletalMesh.h"
#include "ThumbnailHelpers.h"
#include "ThumbnailToTextureSettings.h"

UCustomSkeletalMeshThumbnailRenderer::UCustomSkeletalMeshThumbnailRenderer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCustomSkeletalMeshThumbnailRenderer::Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily)
{
	USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(Object);
	TSharedRef<FCustomSkeletalMeshThumbnailScene> ThumbnailScene = ThumbnailSceneCache.EnsureThumbnailScene(Object);

	if(SkeletalMesh)
	{
		ThumbnailScene->SetSkeletalMesh(SkeletalMesh);
	}
	AddAdditionalPreviewSceneContent(Object, ThumbnailScene->GetWorld());

	FSceneViewFamilyContext ViewFamily( FSceneViewFamily::ConstructionValues( RenderTarget, ThumbnailScene->GetScene(), FEngineShowFlags(ESFIM_Game) )
		.SetTime(GetTime())
		.SetAdditionalViewFamily(bAdditionalViewFamily));

	ViewFamily.EngineShowFlags.DisableAdvancedFeatures();
	ViewFamily.EngineShowFlags.MotionBlur = 0;
	ViewFamily.EngineShowFlags.LOD = 0;

	IThumbnailToTextureToolModule& Module = FModuleManager::GetModuleChecked<IThumbnailToTextureToolModule>("ThumbnailToTextureTool");

	const bool IsTransparent = Module.GetEditorSettings().UseTransparentBackground;
	UMaterial* MaterialInstance = Cast<UMaterial>( Module.GetEditorSettings().GetBackgroundMaterial());
	ThumbnailScene->SetMaterial(MaterialInstance, IsTransparent);
	
	RenderViewFamily(Canvas, &ViewFamily, ThumbnailScene->CreateView(&ViewFamily, X, Y, Width, Height));
	ThumbnailScene->SetSkeletalMesh(nullptr);
}

EThumbnailRenderFrequency UCustomSkeletalMeshThumbnailRenderer::GetThumbnailRenderFrequency(UObject* Object) const
{
	USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(Object);
	return SkeletalMesh && SkeletalMesh->GetResourceForRendering() 
		? EThumbnailRenderFrequency::Realtime
		: EThumbnailRenderFrequency::OnPropertyChange;
}

bool UCustomSkeletalMeshThumbnailRenderer::CanVisualizeAsset(UObject* Object)
{
	if (!Super::CanVisualizeAsset(Object))
	{
		return false;
	}
	USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(Object);
	const bool bValidRenderData = SkeletalMesh && !SkeletalMesh->IsCompiling() && SkeletalMesh->GetResourceForRendering();
	return bValidRenderData;
}

void UCustomSkeletalMeshThumbnailRenderer::BeginDestroy()
{
	ThumbnailSceneCache.Clear();

	Super::BeginDestroy();
}
