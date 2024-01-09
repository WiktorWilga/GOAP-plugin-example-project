// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "BHGameplayAbilityTargetActor.h"
#include "BHGAT_ActorArray.generated.h"

/**
 * Gameplay target actor which returns array of actors.
 */
UCLASS()
class BRAINHACKER_API ABHGAT_ActorArray : public ABHGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:

	/** Overriden to return custom type (actors array). */
	virtual void ConfirmTargetingAndContinue() override;

protected:

	/** This array need to be set before confirm target. It will be returned. */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TArray<TSoftObjectPtr<AActor>> TargetedActors;
	
};
