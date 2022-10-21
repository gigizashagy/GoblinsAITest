// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AITurtles : ModuleRules
{
	public AITurtles(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "GameplayTasks" });
	}
}
