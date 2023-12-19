// Credits please, open source from NanceDevDiaries. Game on!

#pragma once

#include "CoreMinimal.h"
#include "ThumbnailRendering/DefaultSizedThumbnailRenderer.h"
#include "CustomStaticMeshThumbnailRenderer.generated.h"

/**
 * 
 */
UCLASS(config=Editor)
class THUMBNAILTOTEXTURETOOL_API UCustomStaticMeshThumbnailRenderer : public UDefaultSizedThumbnailRenderer
{
	GENERATED_UCLASS_BODY()


	// Begin UThumbnailRenderer Object
	virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily) override;
	// End UThumbnailRenderer Object

	// UObject implementation
	virtual void BeginDestroy() override;

private:
	class FCustomStaticMeshThumbnailScene* ThumbnailScene;
};
