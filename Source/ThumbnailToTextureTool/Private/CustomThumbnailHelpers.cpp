// Credits please, open source from NanceDevDiaries. Game on!

#include "CustomThumbnailHelpers.h"

#include "ContentStreaming.h"
#include "Math/MathFwd.h"
#include "UnrealEdGlobals.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/DirectionalLightComponent.h"
#include "Editor/UnrealEdEngine.h"
#include "Engine/StaticMeshActor.h"
#include "ThumbnailRendering/SceneThumbnailInfo.h"
#include "ThumbnailRendering/ThumbnailManager.h"

FCustomThumbnailPreviewScene::FCustomThumbnailPreviewScene()
: FPreviewScene( ConstructionValues()
						.SetLightRotation( FRotator(304.736, 39.84, 0) )
						.SetSkyBrightness(1.69f)
						.SetCreatePhysicsScene(false)
						.SetTransactional(false))
{	
	// Adjust the default light
	DirectionalLight->Intensity = 0.2f;

	// Add additional lights
	UDirectionalLightComponent* DirectionalLight2 = NewObject<UDirectionalLightComponent>();
	DirectionalLight2->Intensity = 5.0f;
	DirectionalLight2->ForwardShadingPriority = 1;
	FPreviewScene::AddComponent(DirectionalLight2, FTransform( FRotator(-40,-144.678, 0) ));

	UDirectionalLightComponent* DirectionalLight3 = NewObject<UDirectionalLightComponent>();
	DirectionalLight3->Intensity = 1.0f;
	DirectionalLight2->ForwardShadingPriority = 2;
	FPreviewScene::AddComponent(DirectionalLight3, FTransform( FRotator(299.235,144.993, 0) ));
	
	SetSkyCubemap(GUnrealEd->GetThumbnailManager()->AmbientCubemap);

	// NOTE (NanceDevDiaries) this is the main change, BackgroundSkySphereComponent and BackgroundPlaneComponent
	// Can be modified because of this change. In the thumbnail preview scene those are not editable
	// A background sky sphere
	BackgroundSkySphereComponent = NewObject<UStaticMeshComponent>();
	BackgroundSkySphereComponent->SetStaticMesh( GUnrealEd->GetThumbnailManager()->EditorSkySphere );
	const float SkySphereScale = 2000.0f;
	const FTransform BackgroundTransform(FRotator(0,0,0), FVector(0,0,0), FVector(SkySphereScale));
	FPreviewScene::AddComponent(BackgroundSkySphereComponent, BackgroundTransform);
	
	BackgroundPlaneComponent = NewObject<UStaticMeshComponent>(GetTransientPackage());
	BackgroundPlaneComponent->SetStaticMesh(GUnrealEd->GetThumbnailManager()->EditorPlane);
	BackgroundPlaneComponent->bSelectable = false;
	
	// Add an infinite plane
	const float FloorPlaneScale = 10000.f;
	const FTransform FloorPlaneTransform(FRotator(-90.f,0,0), FVector::ZeroVector, FVector(FloorPlaneScale));
	FPreviewScene::AddComponent(BackgroundPlaneComponent, FloorPlaneTransform);
}

PRAGMA_DISABLE_DEPRECATION_WARNINGS
void FCustomThumbnailPreviewScene::GetView(FSceneViewFamily* ViewFamily, int32 X, int32 Y, uint32 SizeX, uint32 SizeY) const
{
	// CreateView allocates a FSceneView, which is only accessible as a const pointer in FSceneViewFamily afterwards so CreateView is the new way and is marked as [[nodiscard]], hence the static_cast<void>, to avoid a compiler warning :
	static_cast<void>(CreateView(ViewFamily, X, Y, SizeX, SizeY)); 
}
PRAGMA_ENABLE_DEPRECATION_WARNINGS

FSceneView* FCustomThumbnailPreviewScene::CreateView(FSceneViewFamily * ViewFamily, int32 X, int32 Y, uint32 SizeX, uint32 SizeY) const
{
	check(ViewFamily);

	FIntRect ViewRect(
		FMath::Max<int32>(X,0),
		FMath::Max<int32>(Y,0),
		FMath::Max<int32>(X+SizeX,0),
		FMath::Max<int32>(Y+SizeY,0));

	if (ViewRect.Area() <= 0)
	{
		return nullptr;
	}
		
	const float FOVDegrees = 30.f;
	const float HalfFOVRadians = FMath::DegreesToRadians<float>(FOVDegrees) * 0.5f;
	static_assert((int32)ERHIZBuffer::IsInverted != 0, "Check NearPlane and Projection Matrix");
	const float NearPlane = 1.0f;
	FMatrix ProjectionMatrix = FReversedZPerspectiveMatrix(
		HalfFOVRadians,
		1.0f,
		1.0f,
		NearPlane
		);

	FVector Origin(0);
	float OrbitPitch = 0;
	float OrbitYaw = 0;
	float OrbitZoom = 0;
	GetViewMatrixParameters(FOVDegrees, Origin, OrbitPitch, OrbitYaw, OrbitZoom);

	// Ensure a minimum camera distance to prevent problems with really small objects
	const float MinCameraDistance = 48;
	OrbitZoom = FMath::Max<float>(MinCameraDistance, OrbitZoom);

	const FRotator RotationOffsetToViewCenter(0.f, 90.f, 0.f);
	FMatrix ViewRotationMatrix = FRotationMatrix( FRotator(0, OrbitYaw, 0) ) * 
		FRotationMatrix( FRotator(0, 0, OrbitPitch) ) *
		FTranslationMatrix( FVector(0, OrbitZoom, 0) ) *
		FInverseRotationMatrix( RotationOffsetToViewCenter );

	ViewRotationMatrix = ViewRotationMatrix * FMatrix(
		FPlane(0,	0,	1,	0),
		FPlane(1,	0,	0,	0),
		FPlane(0,	1,	0,	0),
		FPlane(0,	0,	0,	1));

	Origin -= ViewRotationMatrix.InverseTransformPosition(FVector::ZeroVector);
	ViewRotationMatrix = ViewRotationMatrix.RemoveTranslation();

	FSceneViewInitOptions ViewInitOptions;
	ViewInitOptions.ViewFamily = ViewFamily;
	ViewInitOptions.SetViewRectangle(ViewRect);
	ViewInitOptions.ViewOrigin = -Origin;
	ViewInitOptions.ViewRotationMatrix = ViewRotationMatrix;
	ViewInitOptions.ProjectionMatrix = ProjectionMatrix;
	ViewInitOptions.BackgroundColor = FLinearColor::Black;

	FSceneView* NewView = new FSceneView(ViewInitOptions);

	ViewFamily->Views.Add(NewView);

	NewView->StartFinalPostprocessSettings( ViewInitOptions.ViewOrigin );
	NewView->EndFinalPostprocessSettings(ViewInitOptions);
		
	// Tell the texture streaming system about this thumbnail view, so the textures will stream in as needed
	// NOTE: Sizes may not actually be in screen space depending on how the thumbnail ends up stretched by the UI.  Not a big deal though.
	// NOTE: Textures still take a little time to stream if the view has not been re-rendered recently, so they may briefly appear blurry while mips are prepared
	// NOTE: Content Browser only renders thumbnails for loaded assets, and only when the mouse is over the panel. They'll be frozen in their last state while the mouse cursor is not over the panel.  This is for performance reasons
	float ScreenSize = static_cast<float>(SizeX);
	float FOVScreenSize = static_cast<float>(SizeX) / FMath::Tan(FOVDegrees);
	IStreamingManager::Get().AddViewInformation(Origin, ScreenSize, FOVScreenSize);

	return NewView;
}

void FCustomThumbnailPreviewScene::Tick(float DeltaTime)
{
	UpdateCaptureContents();
}

TStatId FCustomThumbnailPreviewScene::GetStatId() const
{
	return TStatId();
}

void FCustomThumbnailPreviewScene::SetMaterial(UMaterial* Material, bool IsTransparent)
{
	if (Material)
	{
		BackgroundSkySphereComponent->SetMaterial(0, Material);
		BackgroundSkySphereComponent->SetVisibility(true, true);
		BackgroundPlaneComponent->SetMaterial(0, Material);
		BackgroundPlaneComponent->SetVisibility(true, true);
	}
	else
	{
		if (IsTransparent)
		{
			BackgroundSkySphereComponent->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial")));
			BackgroundPlaneComponent->SetMaterial(0, LoadObject<UMaterial>(nullptr, TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial")));
		}
		else
		{
			BackgroundSkySphereComponent->SetVisibility(false, true);
			BackgroundPlaneComponent->SetVisibility(false, true);
		}
	}
}

float FCustomThumbnailPreviewScene::GetBoundsZOffset(const FBoxSphereBounds& Bounds) const
{
	// Return half the height of the bounds plus one to avoid ZFighting with the floor plane
	return static_cast<float>(Bounds.BoxExtent.Z + 1.0);
}

/*
***************************************************************
  FCustomClassActorThumbnailScene
***************************************************************
*/

FCustomClassActorThumbnailScene::FCustomClassActorThumbnailScene()
	: FCustomThumbnailPreviewScene()
	, NumStartingActors(0)
	, PreviewActor(nullptr)
{
	NumStartingActors = GetWorld()->GetCurrentLevel()->Actors.Num();
}

void FCustomClassActorThumbnailScene::SpawnPreviewActor(UClass* InClass)
{
	if (PreviewActor.IsStale())
	{
		PreviewActor = nullptr;
		ClearStaleActors();
	}

	if (PreviewActor.IsValid())
	{
		if (PreviewActor->GetClass() == InClass)
		{
			return;
		}

		PreviewActor->Destroy();
		PreviewActor = nullptr;
	}
	if (InClass && !InClass->HasAnyClassFlags(CLASS_Deprecated | CLASS_Abstract))
	{
		// Create preview actor
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.bNoFail = true;
		SpawnInfo.ObjectFlags = RF_Transient;
		PreviewActor = GetWorld()->SpawnActor<AActor>(InClass, SpawnInfo);

		if (PreviewActor.IsValid())
		{
			const FBoxSphereBounds Bounds = GetPreviewActorBounds();
			const float BoundsZOffset = GetBoundsZOffset(Bounds);
			const FTransform Transform(-Bounds.Origin + FVector(0, 0, BoundsZOffset));

			PreviewActor->SetActorTransform(Transform);
		}
	}
}

void FCustomClassActorThumbnailScene::ClearStaleActors()
{
	ULevel* Level = GetWorld()->GetCurrentLevel();

	for (int32 i = NumStartingActors; i < Level->Actors.Num(); ++i)
	{
		if (Level->Actors[i])
		{
			Level->Actors[i]->Destroy();
		}
	}
}

bool FCustomClassActorThumbnailScene::IsValidComponentForVisualization(const UActorComponent* Component)
{
	const UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Component);
	if ( PrimComp && PrimComp->IsVisible() && !PrimComp->bHiddenInGame )
	{
		const UStaticMeshComponent* StaticMeshComp = Cast<UStaticMeshComponent>(Component);
		if ( StaticMeshComp && StaticMeshComp->GetStaticMesh())
		{
			return true;
		}

		const USkeletalMeshComponent* SkelMeshComp = Cast<USkeletalMeshComponent>(Component);
		if ( SkelMeshComp && SkelMeshComp->GetSkeletalMeshAsset())
		{
			return true;
		}

		// we cannot include the geomety collection component in this module because of circular dependency 
		// so we need to check using the name of the class instead 
		const FName ClassName = Component->GetClass()->GetFName();
		const FName GeometryCollectionClassName("GeometryCollectionComponent");
		if (ClassName == GeometryCollectionClassName)
		{
			return true;
		}
	}

	return false;
}

FBoxSphereBounds FCustomClassActorThumbnailScene::GetPreviewActorBounds() const
{
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION <= 2
	FBoxSphereBounds BoundsBuilder;
#else
	FBoxSphereBounds::Builder BoundsBuilder;
#endif
	if (PreviewActor.IsValid() && PreviewActor->GetRootComponent())
	{
		TArray<USceneComponent*> PreviewComponents;
		PreviewActor->GetRootComponent()->GetChildrenComponents(true, PreviewComponents);
		PreviewComponents.Add(PreviewActor->GetRootComponent());

		for (USceneComponent* PreviewComponent : PreviewComponents)
		{
			if (IsValidComponentForVisualization(PreviewComponent))
			{
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION <= 2
				BoundsBuilder = Union(BoundsBuilder, PreviewComponent->Bounds);
#else
				BoundsBuilder += PreviewComponent->Bounds;
#endif
			}
		}
	}

	return BoundsBuilder;
}

void FCustomClassActorThumbnailScene::GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const
{
	const float HalfFOVRadians = FMath::DegreesToRadians<float>(InFOVDegrees) * 0.5f;
	// Add extra size to view slightly outside of the sphere to compensate for perspective
	const FBoxSphereBounds Bounds = GetPreviewActorBounds();

	const float HalfMeshSize = static_cast<float>(Bounds.SphereRadius * 1.15);
	const float BoundsZOffset = GetBoundsZOffset(Bounds);
	const float TargetDistance = HalfMeshSize / FMath::Tan(HalfFOVRadians);

	USceneThumbnailInfo* ThumbnailInfo = GetSceneThumbnailInfo(TargetDistance);
	check(ThumbnailInfo);

	OutOrigin = FVector(0, 0, -BoundsZOffset);
	OutOrbitPitch = ThumbnailInfo->OrbitPitch;
	OutOrbitYaw = ThumbnailInfo->OrbitYaw;
	OutOrbitZoom = TargetDistance + ThumbnailInfo->OrbitZoom;
}

/*
***************************************************************
  FBlueprintThumbnailScene
***************************************************************
*/

FCustomBlueprintThumbnailScene::FCustomBlueprintThumbnailScene()
	: CurrentBlueprint(nullptr)
{
}

void FCustomBlueprintThumbnailScene::SetBlueprint(UBlueprint* Blueprint)
{
	CurrentBlueprint = Blueprint;
	UClass* BPClass = (Blueprint ? Blueprint->GeneratedClass : nullptr);
	SpawnPreviewActor(BPClass);
}

void FCustomBlueprintThumbnailScene::BlueprintChanged(UBlueprint* Blueprint)
{
	if (CurrentBlueprint == Blueprint)
	{
		UClass* BPClass = (Blueprint ? Blueprint->GeneratedClass : nullptr);
		SpawnPreviewActor(BPClass);
	}
}

USceneThumbnailInfo* FCustomBlueprintThumbnailScene::GetSceneThumbnailInfo(const float TargetDistance) const
{
	UBlueprint* Blueprint = CurrentBlueprint.Get();
	check(Blueprint);

	USceneThumbnailInfo* ThumbnailInfo = Cast<USceneThumbnailInfo>(Blueprint->ThumbnailInfo);
	if ( ThumbnailInfo )
	{
		if ( TargetDistance + ThumbnailInfo->OrbitZoom < 0 )
		{
			ThumbnailInfo->OrbitZoom = -TargetDistance;
		}
	}
	else
	{
		ThumbnailInfo = USceneThumbnailInfo::StaticClass()->GetDefaultObject<USceneThumbnailInfo>();
	}

	return ThumbnailInfo;
}

/*
***************************************************************
  FSkeletalMeshThumbnailScene
***************************************************************
*/

FCustomSkeletalMeshThumbnailScene::FCustomSkeletalMeshThumbnailScene()
{
	bForceAllUsedMipsResident = false;
	// Create preview actor
	// checked
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.bNoFail = true;
	SpawnInfo.ObjectFlags = RF_Transient;
	PreviewActor = GetWorld()->SpawnActor<ASkeletalMeshActor>( SpawnInfo );

	PreviewActor->SetActorEnableCollision(false);
}

void FCustomSkeletalMeshThumbnailScene::SetSkeletalMesh(USkeletalMesh* InSkeletalMesh)
{
	PreviewActor->GetSkeletalMeshComponent()->OverrideMaterials.Empty();
	PreviewActor->GetSkeletalMeshComponent()->SetSkeletalMesh(InSkeletalMesh, false);
	PreviewActor->GetSkeletalMeshComponent()->SetDrawDebugSkeleton(bDrawDebugSkeleton);
	PreviewActor->GetSkeletalMeshComponent()->SetDebugDrawColor(DrawDebugColor);

	if ( InSkeletalMesh )
	{
		FTransform MeshTransform = FTransform::Identity;

		PreviewActor->SetActorLocation(FVector(0,0,0), false);
		PreviewActor->GetSkeletalMeshComponent()->UpdateBounds();

		// Center the mesh at the world origin then offset to put it on top of the plane
		const float BoundsZOffset = GetBoundsZOffset(PreviewActor->GetSkeletalMeshComponent()->Bounds);
		PreviewActor->SetActorLocation( -PreviewActor->GetSkeletalMeshComponent()->Bounds.Origin + FVector(0, 0, BoundsZOffset), false );
		PreviewActor->GetSkeletalMeshComponent()->RecreateRenderState_Concurrent();
	}
	else
	{
		PreviewActor->GetSkeletalMeshComponent()->ClearAnimScriptInstance();
	}
}

void FCustomSkeletalMeshThumbnailScene::SetDrawDebugSkeleton(bool bInDrawDebugSkeleton, const FLinearColor& InSkeletonColor)
{
 	bDrawDebugSkeleton = bInDrawDebugSkeleton;
	DrawDebugColor = InSkeletonColor;
	PreviewActor->GetSkeletalMeshComponent()->SetDrawDebugSkeleton(bDrawDebugSkeleton);
	PreviewActor->GetSkeletalMeshComponent()->SetDebugDrawColor(DrawDebugColor);
	PreviewActor->GetSkeletalMeshComponent()->RecreateRenderState_Concurrent();
}

void FCustomSkeletalMeshThumbnailScene::GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const
{
	check(PreviewActor->GetSkeletalMeshComponent());

	const float HalfFOVRadians = FMath::DegreesToRadians<float>(InFOVDegrees) * 0.5f;
	// No need to add extra size to view slightly outside of the sphere to compensate for perspective since skeletal meshes already buffer bounds.
	const float HalfMeshSize = static_cast<float>(PreviewActor->GetSkeletalMeshComponent()->Bounds.SphereRadius); 
	const float BoundsZOffset = GetBoundsZOffset(PreviewActor->GetSkeletalMeshComponent()->Bounds);
	const float TargetDistance = HalfMeshSize / FMath::Tan(HalfFOVRadians);

	USceneThumbnailInfo* ThumbnailInfo = nullptr;
	if(PreviewActor->GetSkeletalMeshComponent()->GetSkeletalMeshAsset())
	{
		ThumbnailInfo = Cast<USceneThumbnailInfo>(PreviewActor->GetSkeletalMeshComponent()->GetSkeletalMeshAsset()->GetThumbnailInfo());
	}
	
	if ( ThumbnailInfo )
	{
		if ( TargetDistance + ThumbnailInfo->OrbitZoom < 0 )
		{
			ThumbnailInfo->OrbitZoom = -TargetDistance;
		}
	}
	else
	{
		ThumbnailInfo = USceneThumbnailInfo::StaticClass()->GetDefaultObject<USceneThumbnailInfo>();
	}

	OutOrigin = FVector(0, 0, -BoundsZOffset);
	OutOrbitPitch = ThumbnailInfo->OrbitPitch;
	OutOrbitYaw = ThumbnailInfo->OrbitYaw;
	OutOrbitZoom = TargetDistance + ThumbnailInfo->OrbitZoom;
}

/*
***************************************************************
  FStaticMeshThumbnailScene
***************************************************************
*/

FCustomStaticMeshThumbnailScene::FCustomStaticMeshThumbnailScene()
{
	bForceAllUsedMipsResident = false;

	// Create preview actor
	// checked
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.bNoFail = true;
	SpawnInfo.ObjectFlags = RF_Transient;
	PreviewActor = GetWorld()->SpawnActor<AStaticMeshActor>( SpawnInfo );

	PreviewActor->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	PreviewActor->SetActorEnableCollision(false);
}

void FCustomStaticMeshThumbnailScene::SetStaticMesh(UStaticMesh* StaticMesh)
{
	PreviewActor->GetStaticMeshComponent()->SetStaticMesh(StaticMesh);

	if ( StaticMesh )
	{
		FTransform MeshTransform = FTransform::Identity;

		PreviewActor->SetActorLocation(FVector(0,0,0), false);
		
		//Force LOD 0
		PreviewActor->GetStaticMeshComponent()->ForcedLodModel = 1;

		PreviewActor->GetStaticMeshComponent()->UpdateBounds();

		// Center the mesh at the world origin then offset to put it on top of the plane
		const float BoundsZOffset = GetBoundsZOffset(PreviewActor->GetStaticMeshComponent()->Bounds);
		PreviewActor->SetActorLocation( -PreviewActor->GetStaticMeshComponent()->Bounds.Origin + FVector(0, 0, BoundsZOffset), false );
	}

	PreviewActor->GetStaticMeshComponent()->RecreateRenderState_Concurrent();
}

void FCustomStaticMeshThumbnailScene::SetOverrideMaterials(const TArray<class UMaterialInterface*>& OverrideMaterials)
{
	PreviewActor->GetStaticMeshComponent()->OverrideMaterials = OverrideMaterials;
	PreviewActor->GetStaticMeshComponent()->MarkRenderStateDirty();
}

void FCustomStaticMeshThumbnailScene::GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const
{
	check(PreviewActor);
	check(PreviewActor->GetStaticMeshComponent());
	check(PreviewActor->GetStaticMeshComponent()->GetStaticMesh());

	const float HalfFOVRadians = FMath::DegreesToRadians<float>(InFOVDegrees) * 0.5f;
	// Add extra size to view slightly outside of the sphere to compensate for perspective
	const float HalfMeshSize = static_cast<float>(PreviewActor->GetStaticMeshComponent()->Bounds.SphereRadius * 1.15);
	const float BoundsZOffset = GetBoundsZOffset(PreviewActor->GetStaticMeshComponent()->Bounds);
	const float TargetDistance = HalfMeshSize / FMath::Tan(HalfFOVRadians);

	USceneThumbnailInfo* ThumbnailInfo = Cast<USceneThumbnailInfo>(PreviewActor->GetStaticMeshComponent()->GetStaticMesh()->ThumbnailInfo);
	if ( ThumbnailInfo )
	{
		if ( TargetDistance + ThumbnailInfo->OrbitZoom < 0 )
		{
			ThumbnailInfo->OrbitZoom = -TargetDistance;
		}
	}
	else
	{
		ThumbnailInfo = USceneThumbnailInfo::StaticClass()->GetDefaultObject<USceneThumbnailInfo>();
	}

	OutOrigin = FVector(0, 0, -BoundsZOffset);
	OutOrbitPitch = ThumbnailInfo->OrbitPitch;
	OutOrbitYaw = ThumbnailInfo->OrbitYaw;
	OutOrbitZoom = TargetDistance + ThumbnailInfo->OrbitZoom;
}


