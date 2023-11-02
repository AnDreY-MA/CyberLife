// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CyberLife : ModuleRules
{
	public CyberLife(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "ApexDestruction" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
