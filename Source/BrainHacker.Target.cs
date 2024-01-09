// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

using UnrealBuildTool;
using System.Collections.Generic;

public class BrainHackerTarget : TargetRules
{
	public BrainHackerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("BrainHacker");
	}
}
