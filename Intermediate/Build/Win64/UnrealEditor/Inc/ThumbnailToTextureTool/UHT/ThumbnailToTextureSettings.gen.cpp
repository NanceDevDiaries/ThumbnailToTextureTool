// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ThumbnailToTextureTool/Public/ThumbnailToTextureSettings.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeThumbnailToTextureSettings() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FDirectoryPath();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FSoftObjectPath();
	ENGINE_API UClass* Z_Construct_UClass_UMaterial_NoRegister();
	THUMBNAILTOTEXTURETOOL_API UClass* Z_Construct_UClass_UThumbnailToTextureSettings();
	THUMBNAILTOTEXTURETOOL_API UClass* Z_Construct_UClass_UThumbnailToTextureSettings_NoRegister();
	UPackage* Z_Construct_UPackage__Script_ThumbnailToTextureTool();
// End Cross Module References
	void UThumbnailToTextureSettings::StaticRegisterNativesUThumbnailToTextureSettings()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UThumbnailToTextureSettings);
	UClass* Z_Construct_UClass_UThumbnailToTextureSettings_NoRegister()
	{
		return UThumbnailToTextureSettings::StaticClass();
	}
	struct Z_Construct_UClass_UThumbnailToTextureSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RootTexture2DSaveDir_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_RootTexture2DSaveDir;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ThumbnailPrefix_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_ThumbnailPrefix;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_UseCustomBackgroundMaterial_MetaData[];
#endif
		static void NewProp_UseCustomBackgroundMaterial_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_UseCustomBackgroundMaterial;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BackgroundMaterial_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_BackgroundMaterial;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_UseTransparentBackground_MetaData[];
#endif
		static void NewProp_UseTransparentBackground_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_UseTransparentBackground;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BackgroundCutoffThreshold_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_BackgroundCutoffThreshold;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TranslucentMaterial_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_TranslucentMaterial;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UThumbnailToTextureSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_ThumbnailToTextureTool,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UThumbnailToTextureSettings_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UThumbnailToTextureSettings_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "ThumbnailToTextureSettings.h" },
		{ "ModuleRelativePath", "Public/ThumbnailToTextureSettings.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_RootTexture2DSaveDir_MetaData[] = {
		{ "Category", "Thumbnail To Texture Settings" },
		{ "Comment", "/** The root of the directory in which to save the exported Texture2Ds. */" },
		{ "ContentDir", "" },
		{ "DisplayName", "Root Texture 2D Save Directory" },
		{ "ModuleRelativePath", "Public/ThumbnailToTextureSettings.h" },
		{ "ToolTip", "The root of the directory in which to save the exported Texture2Ds." },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_RootTexture2DSaveDir = { "RootTexture2DSaveDir", nullptr, (EPropertyFlags)0x0010000000004005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UThumbnailToTextureSettings, RootTexture2DSaveDir), Z_Construct_UScriptStruct_FDirectoryPath, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_RootTexture2DSaveDir_MetaData), Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_RootTexture2DSaveDir_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_ThumbnailPrefix_MetaData[] = {
		{ "Category", "Thumbnail To Texture Settings" },
		{ "Comment", "/**\n\x09 * The Prefix to append to the name of the exported Texture2Ds\n\x09 */" },
		{ "ModuleRelativePath", "Public/ThumbnailToTextureSettings.h" },
		{ "ToolTip", "The Prefix to append to the name of the exported Texture2Ds" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_ThumbnailPrefix = { "ThumbnailPrefix", nullptr, (EPropertyFlags)0x0010000000004005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UThumbnailToTextureSettings, ThumbnailPrefix), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_ThumbnailPrefix_MetaData), Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_ThumbnailPrefix_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_UseCustomBackgroundMaterial_MetaData[] = {
		{ "Category", "Thumbnail To Texture Settings" },
		{ "Comment", "// If true the thumbnail texture will have a black background, if false it will use the cached thumbnail checkered texture\n" },
		{ "EditCondition", "!UseTransparentBackground" },
		{ "ModuleRelativePath", "Public/ThumbnailToTextureSettings.h" },
		{ "ToolTip", "If true the thumbnail texture will have a black background, if false it will use the cached thumbnail checkered texture" },
	};
#endif
	void Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_UseCustomBackgroundMaterial_SetBit(void* Obj)
	{
		((UThumbnailToTextureSettings*)Obj)->UseCustomBackgroundMaterial = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_UseCustomBackgroundMaterial = { "UseCustomBackgroundMaterial", nullptr, (EPropertyFlags)0x0010000000004005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UThumbnailToTextureSettings), &Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_UseCustomBackgroundMaterial_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_UseCustomBackgroundMaterial_MetaData), Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_UseCustomBackgroundMaterial_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_BackgroundMaterial_MetaData[] = {
		{ "AllowedClasses", "/Script/Engine.MaterialInterface" },
		{ "Category", "Thumbnail To Texture Settings" },
		{ "Comment", "// Material will be set on the background\n" },
		{ "EditCondition", "!UseTransparentBackground && UseCustomBackgroundMaterial" },
		{ "ModuleRelativePath", "Public/ThumbnailToTextureSettings.h" },
		{ "ToolTip", "Material will be set on the background" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_BackgroundMaterial = { "BackgroundMaterial", nullptr, (EPropertyFlags)0x0010000000004005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UThumbnailToTextureSettings, BackgroundMaterial), Z_Construct_UScriptStruct_FSoftObjectPath, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_BackgroundMaterial_MetaData), Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_BackgroundMaterial_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_UseTransparentBackground_MetaData[] = {
		{ "Category", "Thumbnail To Texture Settings" },
		{ "Comment", "// If true the thumbnail texture will have opacity and a transparent background\n" },
		{ "EditCondition", "!UseCustomBackgroundMaterial" },
		{ "ModuleRelativePath", "Public/ThumbnailToTextureSettings.h" },
		{ "ToolTip", "If true the thumbnail texture will have opacity and a transparent background" },
	};
#endif
	void Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_UseTransparentBackground_SetBit(void* Obj)
	{
		((UThumbnailToTextureSettings*)Obj)->UseTransparentBackground = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_UseTransparentBackground = { "UseTransparentBackground", nullptr, (EPropertyFlags)0x0010000000004005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UThumbnailToTextureSettings), &Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_UseTransparentBackground_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_UseTransparentBackground_MetaData), Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_UseTransparentBackground_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_BackgroundCutoffThreshold_MetaData[] = {
		{ "Category", "Thumbnail To Texture Settings" },
		{ "Comment", "// Will cutoff any RGB value that is close to the transparent background color\n" },
		{ "EditCondition", "UseTransparentBackground" },
		{ "ModuleRelativePath", "Public/ThumbnailToTextureSettings.h" },
		{ "ToolTip", "Will cutoff any RGB value that is close to the transparent background color" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_BackgroundCutoffThreshold = { "BackgroundCutoffThreshold", nullptr, (EPropertyFlags)0x0010000000004005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UThumbnailToTextureSettings, BackgroundCutoffThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_BackgroundCutoffThreshold_MetaData), Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_BackgroundCutoffThreshold_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_TranslucentMaterial_MetaData[] = {
		{ "ModuleRelativePath", "Public/ThumbnailToTextureSettings.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_TranslucentMaterial = { "TranslucentMaterial", nullptr, (EPropertyFlags)0x0014000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UThumbnailToTextureSettings, TranslucentMaterial), Z_Construct_UClass_UMaterial_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_TranslucentMaterial_MetaData), Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_TranslucentMaterial_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UThumbnailToTextureSettings_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_RootTexture2DSaveDir,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_ThumbnailPrefix,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_UseCustomBackgroundMaterial,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_BackgroundMaterial,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_UseTransparentBackground,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_BackgroundCutoffThreshold,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UThumbnailToTextureSettings_Statics::NewProp_TranslucentMaterial,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UThumbnailToTextureSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UThumbnailToTextureSettings>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UThumbnailToTextureSettings_Statics::ClassParams = {
		&UThumbnailToTextureSettings::StaticClass,
		"Editor",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UThumbnailToTextureSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UThumbnailToTextureSettings_Statics::PropPointers),
		0,
		0x001000A6u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UThumbnailToTextureSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UThumbnailToTextureSettings_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UThumbnailToTextureSettings_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UThumbnailToTextureSettings()
	{
		if (!Z_Registration_Info_UClass_UThumbnailToTextureSettings.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UThumbnailToTextureSettings.OuterSingleton, Z_Construct_UClass_UThumbnailToTextureSettings_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UThumbnailToTextureSettings.OuterSingleton;
	}
	template<> THUMBNAILTOTEXTURETOOL_API UClass* StaticClass<UThumbnailToTextureSettings>()
	{
		return UThumbnailToTextureSettings::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UThumbnailToTextureSettings);
	UThumbnailToTextureSettings::~UThumbnailToTextureSettings() {}
	struct Z_CompiledInDeferFile_FID_Recordings_PackagedThjumbnailToTexture_Newer_005_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_ThumbnailToTextureSettings_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Recordings_PackagedThjumbnailToTexture_Newer_005_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_ThumbnailToTextureSettings_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UThumbnailToTextureSettings, UThumbnailToTextureSettings::StaticClass, TEXT("UThumbnailToTextureSettings"), &Z_Registration_Info_UClass_UThumbnailToTextureSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UThumbnailToTextureSettings), 3514365620U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Recordings_PackagedThjumbnailToTexture_Newer_005_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_ThumbnailToTextureSettings_h_1383254685(TEXT("/Script/ThumbnailToTextureTool"),
		Z_CompiledInDeferFile_FID_Recordings_PackagedThjumbnailToTexture_Newer_005_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_ThumbnailToTextureSettings_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Recordings_PackagedThjumbnailToTexture_Newer_005_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_ThumbnailToTextureSettings_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
