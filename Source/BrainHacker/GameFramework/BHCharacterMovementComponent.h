// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BHCharacterMovementComponent.generated.h"

UENUM(BlueprintType)
enum class EBHMovementMode : uint8 { Run, Walk, Crouch };

/**
 * Movement component for all characters. Override standard UCharacterMovementComponent to get speed from attributes
 */
UCLASS()
class BRAINHACKER_API UBHCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	UBHCharacterMovementComponent();

	/** Return CurrentValue of speed from characters attributes */
	virtual float GetMaxSpeed() const override;

	/**Change movement mode, which cause change move speed */
	UFUNCTION(BlueprintCallable)
	void SetBHMovementMode(EBHMovementMode NewMovementMode);

protected:

	virtual void BeginPlay() override;

private:

	/** Movement mode, affect character max speed */
	EBHMovementMode MovementMode = EBHMovementMode::Walk;
	/** Reference to character attribute set. Used to get movement speed for modes */
	class UBHAttributeSetBase* OwnerCharacterAttributeSet = nullptr;
};
