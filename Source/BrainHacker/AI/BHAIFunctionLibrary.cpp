// Copyright Wiktor Wilga (wilgawiktor@gmail.com)


#include "BHAIFunctionLibrary.h"


UGOAPPlanner* UBHAIFunctionLibrary::GetGOAPPlanner(const TScriptInterface<IGOAPAgent>& ForAgent)
{
	return ForAgent ? ForAgent->GetGOAPPlanner() : nullptr;
}

UGOAPMemoryComponent* UBHAIFunctionLibrary::GetGOAPMemoryComponent(const TScriptInterface<IGOAPAgent>& ForAgent)
{
	return ForAgent ? ForAgent->GetGOAPMemoryComponent() : nullptr;
}
