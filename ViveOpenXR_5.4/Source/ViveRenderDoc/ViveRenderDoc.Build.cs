// Copyright HTC Corporation. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

namespace UnrealBuildTool.Rules
{
	public class ViveRenderDoc : ModuleRules
	{
		public ViveRenderDoc(ReadOnlyTargetRules Target)
		: base(Target)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					"Projects",
					"OpenXRHMD",
					"VulkanRHI",
					"RHI",
                    "RenderCore",
                    "Renderer",
                    "HeadMountedDisplay"
				}
			);

			AddEngineThirdPartyPrivateStaticDependencies(Target, "Vulkan");
		}
	}
}
