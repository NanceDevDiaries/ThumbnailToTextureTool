// Credits please, open source from NanceDevDiaries. Game on!

#pragma once

#include "CoreMinimal.h"
#include "CustomBlueprintRenderer.h"
#include "CustomSkeletalMeshThumbnailRenderer.h"
#include "CustomStaticMeshThumbnailRenderer.h"
#include "Modules/ModuleManager.h"

class UThumbnailToTextureSettings;

class IThumbnailToTextureToolModule
	: public IModuleInterface
{
public:
	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline IThumbnailToTextureToolModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IThumbnailToTextureToolModule>("ThumbnailToTextureTool");
	}
	
	/**
	* @return reference to Thumbnail To Texture Settings
	*/
	static inline UThumbnailToTextureSettings& GetEditorSettings()
	{
		IThumbnailToTextureToolModule& Module = IsInGameThread() ? Get() : FModuleManager::GetModuleChecked<IThumbnailToTextureToolModule>("ThumbnailToTextureTool");
		UThumbnailToTextureSettings* Settings = Module.GetEditorSettingsInstance();
		check(Settings);
		return *Settings;
	}

	/**
	* @return reference to the custom blueprint renderer, lives in the module
	*/
	static inline UCustomBlueprintRenderer& GetCustomBlueprintThumbnailRenderer()
	{
		IThumbnailToTextureToolModule& Module = IsInGameThread() ? Get() : FModuleManager::GetModuleChecked<IThumbnailToTextureToolModule>("ThumbnailToTextureTool");
		UCustomBlueprintRenderer* ThumbnailRenderer = Module.GetCustomBlueprintThumbnailRendererInstance();
		check(ThumbnailRenderer);
		return *ThumbnailRenderer;
	}

	/**
	* @return reference to the custom StaticMesh renderer, lives in the module
	*/
	static inline UCustomStaticMeshThumbnailRenderer& GetCustomStaticMeshThumbnailRenderer()
	{
		IThumbnailToTextureToolModule& Module = IsInGameThread() ? Get() : FModuleManager::GetModuleChecked<IThumbnailToTextureToolModule>("ThumbnailToTextureTool");
		UCustomStaticMeshThumbnailRenderer* ThumbnailRenderer = Module.GetCustomStaticMeshThumbnailRendererInstance();
		check(ThumbnailRenderer);
		return *ThumbnailRenderer;
	}
	
	/**
	* @return reference to the custom SkeletalMesh renderer, lives in the module
	*/
	static inline UCustomSkeletalMeshThumbnailRenderer& GetCustomSkeletalMeshThumbnailRenderer()
	{
		IThumbnailToTextureToolModule& Module = IsInGameThread() ? Get() : FModuleManager::GetModuleChecked<IThumbnailToTextureToolModule>("ThumbnailToTextureTool");
		UCustomSkeletalMeshThumbnailRenderer* ThumbnailRenderer = Module.GetCustomSkeletalMeshThumbnailRendererInstance();
		check(ThumbnailRenderer);
		return *ThumbnailRenderer;
	}

protected:
	virtual UThumbnailToTextureSettings* GetEditorSettingsInstance() const = 0;
	virtual UCustomBlueprintRenderer* GetCustomBlueprintThumbnailRendererInstance() = 0;
	virtual UCustomStaticMeshThumbnailRenderer* GetCustomStaticMeshThumbnailRendererInstance() = 0;
	virtual UCustomSkeletalMeshThumbnailRenderer* GetCustomSkeletalMeshThumbnailRendererInstance() = 0;
	
};
