// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Input : ModuleRules
{
	public Input(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "GameplayTasks", "GameplayAbilities","UMG", "Slate", 
			"SlateCore", "MotionWarping", "AnimGraphRuntime" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Engine" });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
