// Credits please, open source from NanceDevDiaries. Game on!

#pragma once

#include "CoreMinimal.h"
#include "ThumbnailRendering/BlueprintThumbnailRenderer.h"
#include "CustomBlueprintRenderer.generated.h"

class FCustomBlueprintThumbnailScene;

UCLASS(config=Editor)
class THUMBNAILTOTEXTURETOOL_API UCustomBlueprintRenderer : public UDefaultSizedThumbnailRenderer
{
	GENERATED_UCLASS_BODY()

public:
	// Begin UThumbnailRenderer Object
	virtual bool CanVisualizeAsset(UObject* Object) override;
	virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily) override;
	// End UThumbnailRenderer Object
	
	// UObject implementation
	virtual void BeginDestroy() override;
	// End UObject implementation

	/** Notifies the thumbnail scene to refresh components for the specified blueprint */
	virtual void BlueprintChanged(UBlueprint* Blueprint);

private:
	void OnBlueprintUnloaded(UBlueprint* Blueprint);
	TClassInstanceThumbnailScene<FCustomBlueprintThumbnailScene, 100> CustomThumbnailScenes;
};


