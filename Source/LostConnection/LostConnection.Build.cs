// Copyright (c) 2022 Use-your-imagination

using System;
using System.IO;
using UnrealBuildTool;

public class LostConnection : ModuleRules
{
	public LostConnection(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Slate",
			"SlateCore",
			"UMG",
			"Niagara",
			"AIModule",
			"GameplayTasks",
			"PhysicsCore",
			"NavigationSystem",
			"OnlineSubsystem",
			"OnlineSubsystemUtils"
		});

		PublicIncludePaths.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory),
			Path.Combine(EngineDirectory, "Plugins", "FX", "Niagara", "Source", "Niagara", "Public"),
			Path.Combine(EngineDirectory, "Plugins", "Online", "OnlineSubsystem", "Source", "Public")
		});

		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");

		if (Target.Type == TargetType.Editor)
		{
			MinFilesUsingPrecompiledHeaderOverride = 1;
			bUseUnity = false;
		}
	}
}
