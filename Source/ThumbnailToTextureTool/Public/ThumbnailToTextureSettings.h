// Credits please, open source from NanceDevDiaries. Game on!

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ThumbnailToTextureSettings.generated.h"

/**
 * 
 */
UCLASS(config = Editor, defaultconfig)
class THUMBNAILTOTEXTURETOOL_API UThumbnailToTextureSettings : public UObject
{
	GENERATED_BODY()

	UThumbnailToTextureSettings(const FObjectInitializer& ObjectInitializer);
public:
	/** The root of the directory in which to save the exported Texture2Ds. */
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Thumbnail To Texture Settings", meta = (ContentDir), DisplayName="Root Texture 2D Save Directory")
	FDirectoryPath RootTexture2DSaveDir;

	/**
	 * The Prefix to append to the name of the exported Texture2Ds
	 */
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Thumbnail To Texture Settings")
	FString ThumbnailPrefix;

	// If true the thumbnail texture will have a black background, if false it will use the cached thumbnail checkered texture
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="!UseTransparentBackground"), Category = "Thumbnail To Texture Settings")
	bool UseCustomBackgroundMaterial;

	// Material will be set on the background
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="!UseTransparentBackground && UseCustomBackgroundMaterial", AllowedClasses="/Script/Engine.MaterialInterface"), Category = "Thumbnail To Texture Settings")
	FSoftObjectPath BackgroundMaterial;

	// If true the thumbnail texture will have opacity and a transparent background
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="!UseCustomBackgroundMaterial"), Category = "Thumbnail To Texture Settings")
	bool UseTransparentBackground;
	
	// Will cutoff any RGB value that is close to the transparent background color
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="UseTransparentBackground"), Category = "Thumbnail To Texture Settings")
	float BackgroundCutoffThreshold;

	UPROPERTY(Transient)
	TObjectPtr<UMaterial> TranslucentMaterial;

	UMaterial* GetBackgroundMaterial() const;
};
