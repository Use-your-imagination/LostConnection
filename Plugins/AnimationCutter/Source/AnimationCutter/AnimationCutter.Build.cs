// Copyright (c) 2022 Arkadiy Zakharov

using System;
using System.IO;
using UnrealBuildTool;

public class AnimationCutter : ModuleRules
{
	public AnimationCutter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory, "Public")
        });

        PrivateIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory, "Private")
        });

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "CoreUObject",
            "Engine",
            "Slate",
            "SlateCore",
            "DesktopPlatform",
            "Json",
            "JsonUtilities",
            "EditorStyle",
            "UnrealEd",
            "Persona",
            "AnimationEditor",
            "ContentBrowser",
            "ToolMenus",
            "AnimationModifiers",
            "AssetRegistry"
        });

        DynamicallyLoadedModuleNames.AddRange(new string[]
        {
            
        });
    }
}
