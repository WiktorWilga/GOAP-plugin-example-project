// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "GOAPAgent.h"
#include "GOAPTypes.h"
#include "GOAPPlanner.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BHAIFunctionLibrary.generated.h"

/**
 * Utilities for AI.
 */
UCLASS()
class BRAINHACKER_API UBHAIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Get UGOAPPlanner from agent in BP. */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static UGOAPPlanner* GetGOAPPlanner(const TScriptInterface<IGOAPAgent>& ForAgent);

	/** Get UGOAPMemoryComponent from agent in BP. */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static UGOAPMemoryComponent* GetGOAPMemoryComponent(const TScriptInterface<IGOAPAgent>& ForAgent);
	
};
