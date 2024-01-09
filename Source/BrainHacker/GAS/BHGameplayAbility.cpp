// Copyright Wiktor Wilga (wilgawiktor@gmail.com)


#include "BHGameplayAbility.h"

UBHGameplayAbility::UBHGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

FGameplayTag UBHGameplayAbility::GetTriggerTag()
{
	for(auto Trigger : AbilityTriggers)
	{
		if(Trigger.TriggerSource == EGameplayAbilityTriggerSource::GameplayEvent)
		{
			return Trigger.TriggerTag;
		}
	}
	return FGameplayTag::EmptyTag;
}

bool UBHGameplayAbility::CanBeCanceledBP() const
{
	return CanBeCanceled();
}
