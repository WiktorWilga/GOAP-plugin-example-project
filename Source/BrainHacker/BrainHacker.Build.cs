// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

using UnrealBuildTool;

public class BrainHacker : ModuleRules
{
	public BrainHacker(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] 
        { 
	        "Core", 
	        "CoreUObject", 
	        "Engine", 
	        "InputCore", 
	        "HeadMountedDisplay", 
	        "NavigationSystem", 
	        "AIModule"
        });
        
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"GameplayAbilities", 
			"GameplayTags", 
			"GameplayTasks", 
			"GOAP"
		});
    }
}
