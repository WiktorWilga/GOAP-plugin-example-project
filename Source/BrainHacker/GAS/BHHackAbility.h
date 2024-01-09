// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "BHGameplayAbility.h"
#include "BHHackAbility.generated.h"

/**
 * Base class for hack gameplay abilities.
 */
UCLASS()
class BRAINHACKER_API UBHHackAbility : public UBHGameplayAbility
{
	GENERATED_BODY()

public:

	/** Return time in seconds required to perform hack. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetHackingTime() const { return HackingTime; }
	/** Return max range in which this hack can be performed. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetHackRange() const { return HackRange; }
	/** Return icon, which will be displayed on HUD. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTexture2D* GetHackIcon() const { return HackIcon; }

protected:

	/** Time in seconds required to perform hack. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float HackingTime;
	/** Max range in which this hack can be performed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float HackRange;
	/** Hack icon, which will be displayed on HUD. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* HackIcon;
};
