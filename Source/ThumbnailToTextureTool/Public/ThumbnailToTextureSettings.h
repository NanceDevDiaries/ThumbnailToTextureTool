// Credits please, open source from NanceDevDiaries. Game on!

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ThumbnailToTextureSettings.generated.h"

/**
 * 
 */
UCLASS(config = Editor, defaultconfig)
class THUMBNAILTOTEXTURETOOL_API UThumbnailToTextureSettings : public UObject
{
	GENERATED_BODY()

	UThumbnailToTextureSettings();
public:
	/** The root of the directory in which to save the exported Texture2Ds. */
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Thumbnail To Texture Settings", meta = (ContentDir), DisplayName="Root Texture 2D Save Directory")
	FDirectoryPath RootTexture2DSaveDir;

	/**
	 * The Prefix to append to the name of the exported Texture2Ds
	 */
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Thumbnail To Texture Settings")
	FString ThumbnailPrefix;
};
