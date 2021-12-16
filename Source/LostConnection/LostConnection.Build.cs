// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class LostConnection : ModuleRules
{
    public LostConnection(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        MinFilesUsingPrecompiledHeaderOverride = 1;
        bUseUnity = false;

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
            "OnlineSubsystem",
            "OnlineSubsystemUtils",
            "AIModule",
            "PhysicsCore"
        });

        PublicIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory),
            Path.Combine(EngineDirectory, "Plugins", "FX", "Niagara", "Source", "Niagara", "Public"),
            Path.Combine(EngineDirectory, "Plugins", "Online", "OnlineSubsystem", "Source", "Public")
        });

        DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");
    }
}
