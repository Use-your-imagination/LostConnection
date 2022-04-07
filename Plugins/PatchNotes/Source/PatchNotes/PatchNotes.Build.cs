// Copyright (c) 2022 Arkadiy Zakharov

using System;
using System.IO;
using UnrealBuildTool;

public class PatchNotes : ModuleRules
{
	public PatchNotes(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory, "Public")
		});

		PrivateIncludePaths.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory, "Private"),
			Path.Combine(EngineDirectory, "Source", "Developer", "DesktopPlatform", "Public")
		});

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Projects",
			"InputCore",
			"UnrealEd",
			"ToolMenus",
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"Json",
			"JsonUtilities",
			"DesktopPlatform"
		});

		DynamicallyLoadedModuleNames.AddRange(new string[]
		{

		});
	}
}
