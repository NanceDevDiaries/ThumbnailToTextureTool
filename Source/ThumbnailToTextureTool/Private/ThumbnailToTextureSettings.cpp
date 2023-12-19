// Credits please, open source from NanceDevDiaries. Game on!


#include "ThumbnailToTextureSettings.h"

UThumbnailToTextureSettings::UThumbnailToTextureSettings(const FObjectInitializer& ObjectInitializer): UseCustomBackgroundMaterial(false), UseTransparentBackground(false),
                                                            BackgroundCutoffThreshold(.5f)
{
	RootTexture2DSaveDir.Path = TEXT("/Game/ProceduralTextures/");
	ThumbnailPrefix = TEXT("T_");

	if (!IsRunningCommandlet())
	{
		// Structure to hold one-time initialization
		struct FConstructorStatics
		{
			ConstructorHelpers::FObjectFinder<UMaterial> TranslucentMaterialFromPlugin;

			FConstructorStatics()
				: TranslucentMaterialFromPlugin(TEXT("Material'/ThumbnailToTextureTool/BackgroundMaterialNoShadow.BackgroundMaterialNoShadow'"))
			{
			}
		};
		static FConstructorStatics ConstructorStatics;

		TranslucentMaterial = ConstructorStatics.TranslucentMaterialFromPlugin.Object;
	}
}

UMaterial* UThumbnailToTextureSettings::GetBackgroundMaterial() const
{
	if (UseTransparentBackground)
	{
		return TranslucentMaterial;
	}

	if (UMaterial* LoadedMaterial = Cast<UMaterial>(BackgroundMaterial.ResolveObject()))
	{
		return LoadedMaterial;
	}
	else
	{
		return Cast<UMaterial>(BackgroundMaterial.TryLoad());
	}
}
