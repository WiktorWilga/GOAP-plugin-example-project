// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "BrainHacker/GameFramework/BrainHackerCharacter.h"
#include "BrainHacker/GAS/BHHackAbility.h"
#include "Components/ActorComponent.h"
#include "BHTargetingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSelectedHackChangedDelegate, UBHHackAbility*, Hack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSelectedTargetChangedDelegate, AActor*, Target);

/**
 * This component handle targeting for hack abilities.
 */
UCLASS( ClassGroup=(Custom), Blueprintable, Abstract)
class BRAINHACKER_API UBHTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UBHTargetingComponent();

	/** Called when selected hack changed. */
	UPROPERTY(BlueprintAssignable)
	FSelectedHackChangedDelegate OnSelectedHackChangedDelegate;
	/** Called when selected target changed. */
	UPROPERTY(BlueprintAssignable)
	FSelectedTargetChangedDelegate OnSelectedTargetChangedDelegate;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Return currently selected actor. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE AActor* GetSelectedTarget() const { return SelectedTarget; }

	/** Return currently selected hack index. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetSelectedHackIndex() const { return SelectedHackIndex; }
	/** Return currently selected hack. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UBHHackAbility* GetSelectedHack() const { return AvailableHacks[SelectedHackIndex]; }
	/** Return all available hacks. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<UBHHackAbility*> GetAvailableHacks() const { return AvailableHacks; }

	/** Select next (index + 1) hack from AvailableHacks as active hack. */
	UFUNCTION(BlueprintCallable)
	void SelectNextHack();
	/** Select previous (index -1) hack from AvailableHacks as active hack. */
	UFUNCTION(BlueprintCallable)
	void SelectPreviousHack();
	
protected:

	virtual void BeginPlay() override;

	/** On which collision chanel should be target. */
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> CollisionChannel = ECC_Visibility;
	/** Class of targets characters. */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABrainHackerCharacter> TargetClass;

	/** Collect hacks abilities from owner character. */
	void InitializeAvailableHacks();
	
	/** Return true if given actor is in proper range for current hack. */
	bool CheckIsInRange(const AActor* Actor) const;
	/** Return true if is allowed to change target or ability by player (is not using any hack). */
	bool IsTargetingLocked() const;

	/** Override this in BP to implement custom logic on select actor. */
	UFUNCTION(BlueprintImplementableEvent)
	void OnTargetSelected(AActor* Actor);
	/** Override this in BP to implement custom logic on unselect actor. */
	UFUNCTION(BlueprintImplementableEvent)
	void OnTargetUnselected(AActor* Actor);
	/** Override this in BP to implement custom logic on select hack. */
	UFUNCTION(BlueprintImplementableEvent)
	void OnHackSelected(UBHHackAbility* Hack);
	
private:

	ABrainHackerCharacter* Character;
	UBHAbilitySystemComponent* OwnerAbilitySystemComponent;
	APlayerController* PlayerController;

	AActor* SelectedTarget;

	int32 SelectedHackIndex;
	TArray<UBHHackAbility*> AvailableHacks;
	
};
