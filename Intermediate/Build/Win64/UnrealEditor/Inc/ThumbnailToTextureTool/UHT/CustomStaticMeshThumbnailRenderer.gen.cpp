// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ThumbnailToTextureTool/Public/CustomStaticMeshThumbnailRenderer.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCustomStaticMeshThumbnailRenderer() {}

// Begin Cross Module References
THUMBNAILTOTEXTURETOOL_API UClass* Z_Construct_UClass_UCustomStaticMeshThumbnailRenderer();
THUMBNAILTOTEXTURETOOL_API UClass* Z_Construct_UClass_UCustomStaticMeshThumbnailRenderer_NoRegister();
UNREALED_API UClass* Z_Construct_UClass_UDefaultSizedThumbnailRenderer();
UPackage* Z_Construct_UPackage__Script_ThumbnailToTextureTool();
// End Cross Module References

// Begin Class UCustomStaticMeshThumbnailRenderer
void UCustomStaticMeshThumbnailRenderer::StaticRegisterNativesUCustomStaticMeshThumbnailRenderer()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCustomStaticMeshThumbnailRenderer);
UClass* Z_Construct_UClass_UCustomStaticMeshThumbnailRenderer_NoRegister()
{
	return UCustomStaticMeshThumbnailRenderer::StaticClass();
}
struct Z_Construct_UClass_UCustomStaticMeshThumbnailRenderer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "CustomStaticMeshThumbnailRenderer.h" },
		{ "ModuleRelativePath", "Public/CustomStaticMeshThumbnailRenderer.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCustomStaticMeshThumbnailRenderer>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UCustomStaticMeshThumbnailRenderer_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDefaultSizedThumbnailRenderer,
	(UObject* (*)())Z_Construct_UPackage__Script_ThumbnailToTextureTool,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomStaticMeshThumbnailRenderer_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCustomStaticMeshThumbnailRenderer_Statics::ClassParams = {
	&UCustomStaticMeshThumbnailRenderer::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomStaticMeshThumbnailRenderer_Statics::Class_MetaDataParams), Z_Construct_UClass_UCustomStaticMeshThumbnailRenderer_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCustomStaticMeshThumbnailRenderer()
{
	if (!Z_Registration_Info_UClass_UCustomStaticMeshThumbnailRenderer.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCustomStaticMeshThumbnailRenderer.OuterSingleton, Z_Construct_UClass_UCustomStaticMeshThumbnailRenderer_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCustomStaticMeshThumbnailRenderer.OuterSingleton;
}
template<> THUMBNAILTOTEXTURETOOL_API UClass* StaticClass<UCustomStaticMeshThumbnailRenderer>()
{
	return UCustomStaticMeshThumbnailRenderer::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCustomStaticMeshThumbnailRenderer);
UCustomStaticMeshThumbnailRenderer::~UCustomStaticMeshThumbnailRenderer() {}
// End Class UCustomStaticMeshThumbnailRenderer

// Begin Registration
struct Z_CompiledInDeferFile_FID_Recordings_Plugins_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_CustomStaticMeshThumbnailRenderer_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCustomStaticMeshThumbnailRenderer, UCustomStaticMeshThumbnailRenderer::StaticClass, TEXT("UCustomStaticMeshThumbnailRenderer"), &Z_Registration_Info_UClass_UCustomStaticMeshThumbnailRenderer, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCustomStaticMeshThumbnailRenderer), 3217053208U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Recordings_Plugins_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_CustomStaticMeshThumbnailRenderer_h_3544260009(TEXT("/Script/ThumbnailToTextureTool"),
	Z_CompiledInDeferFile_FID_Recordings_Plugins_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_CustomStaticMeshThumbnailRenderer_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Recordings_Plugins_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_CustomStaticMeshThumbnailRenderer_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
