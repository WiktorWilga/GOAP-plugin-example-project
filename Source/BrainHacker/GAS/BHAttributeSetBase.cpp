// Copyright Wiktor Wilga (wilgawiktor@gmail.com)


#include "BHAttributeSetBase.h"

UBHAttributeSetBase::UBHAttributeSetBase()
{
}

void UBHAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UBHAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}
