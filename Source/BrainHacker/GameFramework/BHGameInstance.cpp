// Copyright Wiktor Wilga (wilgawiktor@gmail.com)


#include "BHGameInstance.h"
#include "AbilitySystemGlobals.h"

void UBHGameInstance::Init()
{
	Super::Init();
	
	// need be called to use TargetData
	UAbilitySystemGlobals::Get().InitGlobalData();
}
