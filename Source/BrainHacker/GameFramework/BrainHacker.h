// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBrainHacker, Log, All);

/** Input bindings for GAS */
UENUM(BlueprintType)
enum class EBHAbilityInputID : uint8
{
	// 0 None
	None			UMETA(DisplayName = "None"),
	// 1 Confirm
	Confirm			UMETA(DisplayName = "Confirm"),
	// 2 Cancel
	Cancel			UMETA(DisplayName = "Cancel"),
	// 3 Sprint
	Sprint			UMETA(DisplayName = "Sprint"),
	// 4 Crouch
	Crouch			UMETA(DisplayName = "Crouch"),
};