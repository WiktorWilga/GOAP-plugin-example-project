// Copyright Wiktor Wilga (wilgawiktor@gmail.com)


#include "BHAbilitySystemComponent.h"


UBHAbilitySystemComponent::UBHAbilitySystemComponent()
{
	
}

void UBHAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	OnAbilityEnded.AddUFunction(this, "OnAbilityEndedCallback");
}

TArray<UGameplayAbility*> UBHAbilitySystemComponent::GetActivatableAbilitiesBP()
{
	TArray<FGameplayAbilitySpec> AbilitiesSpec = GetActivatableAbilities();
	TArray<UGameplayAbility*> Abilities;
	for(auto AbilitySpec : AbilitiesSpec)
	{
		Abilities.Add(AbilitySpec.GetAbilityInstances()[0]);
	}
	return Abilities;
}

TArray<UBHGameplayAbility*> UBHAbilitySystemComponent::GetActivatableBHActions()
{
	TArray<UGameplayAbility*> Abilities = GetActivatableAbilitiesBP();
	TArray<UBHGameplayAbility*> Actions;
	for(auto Ability : Abilities)
	{
		UBHGameplayAbility* Action = Cast<UBHGameplayAbility>(Ability);
		if(Action)
			Actions.Add(Action);
	}
	return Actions;
}

TArray<UGameplayAbility*> UBHAbilitySystemComponent::GetActiveAbilities()
{
	TArray<UGameplayAbility*> ActiveAbilities;
	TArray<UGameplayAbility*> Abilities = GetActivatableAbilitiesBP();
	for(auto Ability : Abilities)
	{
		if(Ability->IsActive())
			ActiveAbilities.Add(Ability);
	}
	return ActiveAbilities;
}

bool UBHAbilitySystemComponent::CanActivateAbilityWithTag(const FGameplayTagContainer& AbilityTagContainer) const
{
	TArray<FGameplayAbilitySpec*> AbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagContainer, AbilitySpecs);
	for (auto AbilitySpec : AbilitySpecs)
	{
		if (AbilitySpec->Ability->CanActivateAbility(AbilitySpec->Handle, AbilityActorInfo.Get()))
		{
			return true;
		}
	}
	return false;
}

bool UBHAbilitySystemComponent::CanActivateAbilityClass(const TSubclassOf<UGameplayAbility> AbilityClass) const
{
	if(!IsValid(AbilityClass))
	{
		return false;
	}
	const UGameplayAbility* AbilityCDO = AbilityClass.GetDefaultObject();
	const bool bIsNotCooldown = AbilityCDO->CheckCooldown(FGameplayAbilitySpecHandle(), AbilityActorInfo.Get());	
	const bool bCanActivate = CanActivateAbilityWithTag(AbilityClass.GetDefaultObject()->AbilityTags);
	return bIsNotCooldown && bCanActivate;
}

void UBHAbilitySystemComponent::OnAbilityEndedCallback(const FAbilityEndedData& Data) const
{
	OnActionEnded.Broadcast(Data.AbilityThatEnded, !Data.bWasCancelled);
}

void UBHAbilitySystemComponent::CancelAction_Implementation(UObject* Action)
{
	CancelAbility(Cast<UGameplayAbility>(Action->GetClass()->ClassDefaultObject));
}

UObject* UBHAbilitySystemComponent::GetActiveAction_Implementation()
{
	TArray<UGameplayAbility*> Actions = GetActiveAbilities();
	return Actions.Num() > 0 ? GetActiveAbilities()[0] : nullptr;
}

bool UBHAbilitySystemComponent::TryActivateActionByClass_Implementation(TSubclassOf<UObject> ActionClass)
{
	if(ActionClass)
	{
		if(const UGameplayAbility* AbilityCDO = Cast<UGameplayAbility>(ActionClass->GetDefaultObject(true)))
		{
			return TryActivateAbilityByClass(AbilityCDO->GetClass());
		}
	}
	return false;
}
