// Copyright Wiktor Wilga (wilgawiktor@gmail.com)


#include "BHCharacterMovementComponent.h"
#include "BrainHackerCharacter.h"

UBHCharacterMovementComponent::UBHCharacterMovementComponent()
{
}

void UBHCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	ABrainHackerCharacter* Owner = Cast<ABrainHackerCharacter>(GetOwner());
	ensureMsgf(Owner && Owner->GetAttributeSet(), TEXT("UBHCharacterMovementComponent require ABrainHackerCharacter as "
		"owner and valid attribute set"));
	OwnerCharacterAttributeSet = Owner->GetAttributeSet();
}


float UBHCharacterMovementComponent::GetMaxSpeed() const
{
	switch (MovementMode)
	{
	case EBHMovementMode::Run:
		return OwnerCharacterAttributeSet->GetRunSpeed();
	case EBHMovementMode::Walk:
		return OwnerCharacterAttributeSet->GetWalkSpeed();
	case EBHMovementMode::Crouch:
		return OwnerCharacterAttributeSet->GetCrouchSpeed();
	default:
		UE_LOG(LogTemp, Error, TEXT("%s() UBHCharacterMovementComponent not supports active movement mode. Return base comp value."), *FString(__FUNCTION__));
		return Super::GetMaxSpeed();
	}
}

void UBHCharacterMovementComponent::SetBHMovementMode(EBHMovementMode NewMovementMode)
{
	MovementMode = NewMovementMode;
}