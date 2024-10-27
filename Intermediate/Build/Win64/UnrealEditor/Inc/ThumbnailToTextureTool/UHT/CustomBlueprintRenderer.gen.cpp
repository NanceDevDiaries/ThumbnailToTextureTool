// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ThumbnailToTextureTool/Public/CustomBlueprintRenderer.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCustomBlueprintRenderer() {}

// Begin Cross Module References
THUMBNAILTOTEXTURETOOL_API UClass* Z_Construct_UClass_UCustomBlueprintRenderer();
THUMBNAILTOTEXTURETOOL_API UClass* Z_Construct_UClass_UCustomBlueprintRenderer_NoRegister();
UNREALED_API UClass* Z_Construct_UClass_UDefaultSizedThumbnailRenderer();
UPackage* Z_Construct_UPackage__Script_ThumbnailToTextureTool();
// End Cross Module References

// Begin Class UCustomBlueprintRenderer
void UCustomBlueprintRenderer::StaticRegisterNativesUCustomBlueprintRenderer()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCustomBlueprintRenderer);
UClass* Z_Construct_UClass_UCustomBlueprintRenderer_NoRegister()
{
	return UCustomBlueprintRenderer::StaticClass();
}
struct Z_Construct_UClass_UCustomBlueprintRenderer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "CustomBlueprintRenderer.h" },
		{ "ModuleRelativePath", "Public/CustomBlueprintRenderer.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCustomBlueprintRenderer>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UCustomBlueprintRenderer_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDefaultSizedThumbnailRenderer,
	(UObject* (*)())Z_Construct_UPackage__Script_ThumbnailToTextureTool,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomBlueprintRenderer_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCustomBlueprintRenderer_Statics::ClassParams = {
	&UCustomBlueprintRenderer::StaticClass,
	"Editor",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomBlueprintRenderer_Statics::Class_MetaDataParams), Z_Construct_UClass_UCustomBlueprintRenderer_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCustomBlueprintRenderer()
{
	if (!Z_Registration_Info_UClass_UCustomBlueprintRenderer.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCustomBlueprintRenderer.OuterSingleton, Z_Construct_UClass_UCustomBlueprintRenderer_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCustomBlueprintRenderer.OuterSingleton;
}
template<> THUMBNAILTOTEXTURETOOL_API UClass* StaticClass<UCustomBlueprintRenderer>()
{
	return UCustomBlueprintRenderer::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCustomBlueprintRenderer);
UCustomBlueprintRenderer::~UCustomBlueprintRenderer() {}
// End Class UCustomBlueprintRenderer

// Begin Registration
struct Z_CompiledInDeferFile_FID_Recordings_Plugins_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_CustomBlueprintRenderer_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCustomBlueprintRenderer, UCustomBlueprintRenderer::StaticClass, TEXT("UCustomBlueprintRenderer"), &Z_Registration_Info_UClass_UCustomBlueprintRenderer, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCustomBlueprintRenderer), 3043687795U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Recordings_Plugins_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_CustomBlueprintRenderer_h_1438150238(TEXT("/Script/ThumbnailToTextureTool"),
	Z_CompiledInDeferFile_FID_Recordings_Plugins_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_CustomBlueprintRenderer_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Recordings_Plugins_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_CustomBlueprintRenderer_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
