// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BrainHacker/GameFramework/BrainHacker.h"
#include "BHGameplayAbility.generated.h"

/**
 * Base class for all abilities in BH project
 */
UCLASS()
class BRAINHACKER_API UBHGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UBHGameplayAbility();

	/** Return tag which can trigger this ability by GameplayEvent. */
	UFUNCTION(BlueprintCallable)
	FGameplayTag GetTriggerTag();

	/** Input binding; if is set this ability will be automatically activated on given input */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EBHAbilityInputID AbilityInputID = EBHAbilityInputID::None;

	UFUNCTION(BlueprintCallable)
	bool CanBeCanceledBP() const;
	
};
