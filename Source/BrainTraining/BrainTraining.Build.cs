// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BrainTraining : ModuleRules
{
	public BrainTraining(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "MediaAssets"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[]
		{
			"BrainTraining/Public/UI"
			,"BrainTraining/Public/UI/MainMenu"
			,"BrainTraining/Public/Objects"
			,"BrainTraining/Public/View"
			,"BrainTraining/Public/Maps"
			,"BrainTraining/Public/UI/AttemptLevel"
			,"BrainTraining/Public/Player"
			,"BrainTraining/Public/Player/MainMenu"
			,"BrainTraining/Public/Player/AttemptLevel"
		});
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
