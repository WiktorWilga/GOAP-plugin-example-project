// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

using UnrealBuildTool;
using System.Collections.Generic;

public class BrainHackerEditorTarget : TargetRules
{
	public BrainHackerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("BrainHacker");
	}
}
