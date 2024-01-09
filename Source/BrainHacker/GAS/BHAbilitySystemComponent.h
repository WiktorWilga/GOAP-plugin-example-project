// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BHGameplayAbility.h"
#include "GOAPActionsExecutor.h"
#include "BHAbilitySystemComponent.generated.h"

/**
 * Ability system component to use in all classes of characters in BH
 */
UCLASS()
class BRAINHACKER_API UBHAbilitySystemComponent : public UAbilitySystemComponent, public IGOAPActionsExecutor
{
	GENERATED_BODY()

public:

	UBHAbilitySystemComponent();

	void virtual BeginPlay() override;

	/** Blueprint callable version of GetActivatableAbilities. */
	UFUNCTION(BlueprintCallable)
	TArray<UGameplayAbility*> GetActivatableAbilitiesBP();

	/** Return all BHActions (GOAP abilities) available for component. */
	UFUNCTION(BlueprintCallable)
	TArray<UBHGameplayAbility*> GetActivatableBHActions();

	/** Return all active abilities. */
	UFUNCTION(BlueprintCallable)
	TArray<UGameplayAbility*> GetActiveAbilities();

	/** Return true if there is any ability with given tags that can be currently activated. */
	UFUNCTION(BlueprintCallable, BlueprintPure = false)
	bool CanActivateAbilityWithTag(const FGameplayTagContainer& AbilityTagContainer) const;

	/** Return true if given ability class cen be currently activated. */
	UFUNCTION(BlueprintCallable, BlueprintPure = false)
	bool CanActivateAbilityClass(const TSubclassOf<UGameplayAbility> AbilityClass) const;

	UFUNCTION()
	void OnAbilityEndedCallback(const FAbilityEndedData& Data) const;


	virtual void CancelAction_Implementation(UObject* Action) override;

	virtual UObject* GetActiveAction_Implementation() override;

	virtual bool TryActivateActionByClass_Implementation(TSubclassOf<UObject> ActionClass) override;
};
