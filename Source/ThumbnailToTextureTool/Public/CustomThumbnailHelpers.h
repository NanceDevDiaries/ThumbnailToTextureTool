// Credits please, open source from NanceDevDiaries. Game on!

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

// Preview scenes

class FSceneViewFamily;
class USceneThumbnailInfo;

class FCustomThumbnailPreviewScene : public FPreviewScene, public FTickableEditorObject
{
public:
	FCustomThumbnailPreviewScene();

	UE_DEPRECATED(5.0, "Use CreateView")
	void GetView(FSceneViewFamily* ViewFamily, int32 X, int32 Y, uint32 SizeX, uint32 SizeY) const;

	/** Allocates then adds an FSceneView to the ViewFamily. */
	[[nodiscard]] FSceneView* CreateView(FSceneViewFamily* ViewFamily, int32 X, int32 Y, uint32 SizeX, uint32 SizeY) const;

	/* Begin FTickableEditorObject */
	virtual void Tick(float DeltaTime) override;
	virtual ETickableTickType GetTickableTickType() const override { return ETickableTickType::Always; }
	virtual TStatId GetStatId() const override;
	/* End FTickableEditorObject */

	/** Sets the custom material background */
	void SetMaterial(UMaterial* Material, bool IsTransparent);

protected:
	/** Useful for setting a custom background color or translucent background */
	UStaticMeshComponent* BackgroundPlaneComponent;
	UStaticMeshComponent* BackgroundSkySphereComponent;
	
	/** Helper function to get the bounds offset to display an asset */
	float GetBoundsZOffset(const FBoxSphereBounds& Bounds) const;

	/**
	  * Gets parameters to create a view matrix to be used by CreateView(). Implemented in children classes.
	  * @param InFOVDegrees  The FOV used to display the thumbnail. Often used to calculate the output parameters.
	  * @param OutOrigin	 The origin of the orbit view. Typically the center of the bounds of the target object.
	  * @param OutOrbitPitch The pitch of the orbit cam around the object.
	  * @param OutOrbitYaw	 The yaw of the orbit cam around the object.
	  * @param OutOrbitZoom  The camera distance from the object.
	  */
	virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const = 0;
};

class FCustomClassActorThumbnailScene : public FCustomThumbnailPreviewScene
{
public:

	FCustomClassActorThumbnailScene();

	/** Returns true if this component can be visualized */
	static bool IsValidComponentForVisualization(const UActorComponent* Component);

protected:
	// FThumbnailPreviewScene implementation
	virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;

	/** Sets the object (class or blueprint) used in the next CreateView() */
	void SpawnPreviewActor(class UClass* Obj);

	/** Get the scene thumbnail info to use for the object currently being rendered */
	virtual USceneThumbnailInfo* GetSceneThumbnailInfo(const float TargetDistance) const = 0;

	FBoxSphereBounds GetPreviewActorBounds() const;

private:

	/** Clears out any stale actors in this scene if PreviewActor enters a stale state */
	void ClearStaleActors();

	int32 NumStartingActors;
	TWeakObjectPtr<class AActor> PreviewActor;
};

class FCustomBlueprintThumbnailScene : public FCustomClassActorThumbnailScene
{
public:
	/** Constructor/Destructor */
	FCustomBlueprintThumbnailScene();

	/** Sets the static mesh to use in the next CreateView() */
	void SetBlueprint(class UBlueprint* Blueprint);
	
	/** Refreshes components for the specified blueprint */
	void BlueprintChanged(class UBlueprint* Blueprint);

protected:
	
	/** Get the scene thumbnail info to use for the object currently being rendered */
	virtual USceneThumbnailInfo* GetSceneThumbnailInfo(const float TargetDistance) const override;

private:
	/** The blueprint that is currently being rendered. NULL when not rendering. */
	TWeakObjectPtr<class UBlueprint> CurrentBlueprint;
};

class FCustomSkeletalMeshThumbnailScene : public FCustomThumbnailPreviewScene
{
public:
	/** Constructor */
	FCustomSkeletalMeshThumbnailScene();

	/** Sets the skeletal mesh to use in the next CreateView() */
	void SetSkeletalMesh(class USkeletalMesh* InSkeletalMesh);

	/** Set whether to draw debug skeleton */
	void SetDrawDebugSkeleton(bool bInDrawDebugSkeleton, const FLinearColor& InSkeletonColor);
	
	/** Returns the preview actor within the scene */
	class ASkeletalMeshActor* GetPreviewActor() const { return PreviewActor; }

protected:
	// FThumbnailPreviewScene implementation
	virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;

private:
	/** The skeletal mesh actor used to display all skeletal mesh thumbnails */
	class ASkeletalMeshActor* PreviewActor;

	/** The color used to draw the debug skeleton */
	FLinearColor DrawDebugColor = FLinearColor::White;
	
	/** Whether to draw debug skeleton */
	bool bDrawDebugSkeleton = false;
};

class FCustomStaticMeshThumbnailScene : public FCustomThumbnailPreviewScene
{
public:
	/** Constructor */
	FCustomStaticMeshThumbnailScene();

	/** Sets the static mesh to use in the next CreateView() */
	void SetStaticMesh(class UStaticMesh* StaticMesh);

	/** Sets override materials for the static mesh  */
	void SetOverrideMaterials(const TArray<class UMaterialInterface*>& OverrideMaterials);

protected:
	// FThumbnailPreviewScene implementation
	virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;

private:
	/** The static mesh actor used to display all static mesh thumbnails */
	class AStaticMeshActor* PreviewActor;
};

