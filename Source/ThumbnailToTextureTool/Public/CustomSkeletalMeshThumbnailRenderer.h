// Credits please, open source from NanceDevDiaries. Game on!

#pragma once

#include "CoreMinimal.h"
#include "ThumbnailHelpers.h"
#include "ThumbnailRendering/DefaultSizedThumbnailRenderer.h"
#include "CustomSkeletalMeshThumbnailRenderer.generated.h"

class FCustomSkeletalMeshThumbnailScene;

UCLASS(config=Editor)
class THUMBNAILTOTEXTURETOOL_API UCustomSkeletalMeshThumbnailRenderer : public UDefaultSizedThumbnailRenderer
{
	GENERATED_UCLASS_BODY()

	// Begin UThumbnailRenderer Object
	virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;
	virtual EThumbnailRenderFrequency GetThumbnailRenderFrequency(UObject* Object) const override;
	virtual bool CanVisualizeAsset(UObject* Object) override;
	// End UThumbnailRenderer Object

	// UObject implementation
	virtual void BeginDestroy() override;

	virtual void AddAdditionalPreviewSceneContent(UObject* Object, UWorld* PreviewWorld) {}

protected:
	TObjectInstanceThumbnailScene<FCustomSkeletalMeshThumbnailScene, 128> ThumbnailSceneCache;
};
