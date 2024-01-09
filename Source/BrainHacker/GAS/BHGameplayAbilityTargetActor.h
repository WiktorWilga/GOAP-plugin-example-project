// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "BHGameplayAbilityTargetActor.generated.h"

/**
 * Base class for all targets actors.
 */
UCLASS()
class BRAINHACKER_API ABHGameplayAbilityTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

protected:

	/** Call this in BP to stop targeting and pass target data to ability. */
	UFUNCTION(BlueprintCallable)
	void ConfirmTarget();
	/** Call this in BP to cancel targeting. */
	UFUNCTION(BlueprintCallable)
	void CancelTarget();

	/** Return reference to instigator ability. */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE UGameplayAbility* GetOwningAbility() const { return OwningAbility; }

	/** Handle confirm input in target actor. */
	UFUNCTION(BlueprintNativeEvent)
	void OnConfirmInput();
	/** Handle cancel input in target actor. */
	UFUNCTION(BlueprintNativeEvent)
	void OnCancelInput();
	
};
