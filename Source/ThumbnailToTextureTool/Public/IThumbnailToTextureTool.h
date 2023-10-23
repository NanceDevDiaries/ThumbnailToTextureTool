// Credits please, open source from NanceDevDiaries. Game on!

#pragma once

#include "CoreMinimal.h"
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

protected:
	virtual  UThumbnailToTextureSettings* GetEditorSettingsInstance() const = 0;
};
