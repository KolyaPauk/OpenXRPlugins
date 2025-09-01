// Copyright 2023 PICO Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class PICOOpenXRHMD : ModuleRules
{
    public PICOOpenXRHMD(ReadOnlyTargetRules Target) : base(Target)
    {
        string EngineDir = Path.GetFullPath(Target.RelativeEnginePath);
        PrivateIncludePaths.AddRange(
            new string[]
            {
                EngineDir+"/Plugins/Runtime/OpenXR/Source/OpenXRHMD/Private",
            });

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "HeadMountedDisplay",
                    "XRBase",
                    "InputCore",
                    "OpenXRHMD",
                    "RHI",
                    "RenderCore",
                    "PICOOpenXRLoader",
                    "PICOOpenXRRuntimeSettings",
                    "ProceduralMeshComponent",
            }
            );

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicDependencyModuleNames.AddRange(new string[] {
                    "D3D11RHI",
                    "D3D12RHI"
                });

            if (!bUsePrecompiled || Target.LinkType == TargetLinkType.Monolithic)
            {
                PublicDependencyModuleNames.AddRange(new string[] {
                        "DX11",
                        "DX12"
                    });
            }
        }

        if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Android
            || Target.IsInPlatformGroup(UnrealPlatformGroup.Linux))
        {
            PublicDependencyModuleNames.Add("VulkanRHI");

            if (!bUsePrecompiled || Target.LinkType == TargetLinkType.Monolithic)
            {
                PublicDependencyModuleNames.Add("Vulkan");
            }
        }
    }
}