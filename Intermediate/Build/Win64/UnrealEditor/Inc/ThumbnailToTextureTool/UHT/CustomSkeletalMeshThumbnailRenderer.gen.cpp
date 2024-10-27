// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ThumbnailToTextureTool/Public/CustomSkeletalMeshThumbnailRenderer.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCustomSkeletalMeshThumbnailRenderer() {}

// Begin Cross Module References
THUMBNAILTOTEXTURETOOL_API UClass* Z_Construct_UClass_UCustomSkeletalMeshThumbnailRenderer();
THUMBNAILTOTEXTURETOOL_API UClass* Z_Construct_UClass_UCustomSkeletalMeshThumbnailRenderer_NoRegister();
UNREALED_API UClass* Z_Construct_UClass_UDefaultSizedThumbnailRenderer();
UPackage* Z_Construct_UPackage__Script_ThumbnailToTextureTool();
// End Cross Module References

// Begin Class UCustomSkeletalMeshThumbnailRenderer
void UCustomSkeletalMeshThumbnailRenderer::StaticRegisterNativesUCustomSkeletalMeshThumbnailRenderer()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCustomSkeletalMeshThumbnailRenderer);
UClass* Z_Construct_UClass_UCustomSkeletalMeshThumbnailRenderer_NoRegister()
{
	return UCustomSkeletalMeshThumbnailRenderer::StaticClass();
}
struct Z_Construct_UClass_UCustomSkeletalMeshThumbnailRenderer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "CustomSkeletalMeshThumbnailRenderer.h" },
		{ "ModuleRelativePath", "Public/CustomSkeletalMeshThumbnailRenderer.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCustomSkeletalMeshThumbnailRenderer>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UCustomSkeletalMeshThumbnailRenderer_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDefaultSizedThumbnailRenderer,
	(UObject* (*)())Z_Construct_UPackage__Script_ThumbnailToTextureTool,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomSkeletalMeshThumbnailRenderer_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCustomSkeletalMeshThumbnailRenderer_Statics::ClassParams = {
	&UCustomSkeletalMeshThumbnailRenderer::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomSkeletalMeshThumbnailRenderer_Statics::Class_MetaDataParams), Z_Construct_UClass_UCustomSkeletalMeshThumbnailRenderer_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCustomSkeletalMeshThumbnailRenderer()
{
	if (!Z_Registration_Info_UClass_UCustomSkeletalMeshThumbnailRenderer.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCustomSkeletalMeshThumbnailRenderer.OuterSingleton, Z_Construct_UClass_UCustomSkeletalMeshThumbnailRenderer_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCustomSkeletalMeshThumbnailRenderer.OuterSingleton;
}
template<> THUMBNAILTOTEXTURETOOL_API UClass* StaticClass<UCustomSkeletalMeshThumbnailRenderer>()
{
	return UCustomSkeletalMeshThumbnailRenderer::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCustomSkeletalMeshThumbnailRenderer);
UCustomSkeletalMeshThumbnailRenderer::~UCustomSkeletalMeshThumbnailRenderer() {}
// End Class UCustomSkeletalMeshThumbnailRenderer

// Begin Registration
struct Z_CompiledInDeferFile_FID_Recordings_Plugins_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_CustomSkeletalMeshThumbnailRenderer_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCustomSkeletalMeshThumbnailRenderer, UCustomSkeletalMeshThumbnailRenderer::StaticClass, TEXT("UCustomSkeletalMeshThumbnailRenderer"), &Z_Registration_Info_UClass_UCustomSkeletalMeshThumbnailRenderer, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCustomSkeletalMeshThumbnailRenderer), 1708935824U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Recordings_Plugins_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_CustomSkeletalMeshThumbnailRenderer_h_146266979(TEXT("/Script/ThumbnailToTextureTool"),
	Z_CompiledInDeferFile_FID_Recordings_Plugins_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_CustomSkeletalMeshThumbnailRenderer_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Recordings_Plugins_ThumbnailToTextureTool_HostProject_Plugins_ThumbnailToTextureTool_Source_ThumbnailToTextureTool_Public_CustomSkeletalMeshThumbnailRenderer_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
