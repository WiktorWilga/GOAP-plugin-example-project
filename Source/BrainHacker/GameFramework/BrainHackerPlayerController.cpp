// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#include "BrainHackerPlayerController.h"
#include "BrainHackerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

ABrainHackerPlayerController::ABrainHackerPlayerController()
{
	bShowMouseCursor = true;
}

void ABrainHackerPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	UpdateCharacterRotationToCursor(DeltaTime);
}

void ABrainHackerPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ABrainHackerPlayerController::OnMoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABrainHackerPlayerController::OnMoveRight);
}

void ABrainHackerPlayerController::OnMoveForward(const float Value)
{
	if(!GetCharacter() || Value == 0.0f)
		return;
	
	GetCharacter()->GetMovementComponent()->AddInputVector(FVector(Value, 0.0f, 0.0f));
}

void ABrainHackerPlayerController::OnMoveRight(const float Value)
{
	if(!GetCharacter() || Value == 0.0f)
		return;
	
	GetCharacter()->GetMovementComponent()->AddInputVector(FVector(0.0f, Value, 0.0f));
}

void ABrainHackerPlayerController::UpdateCharacterRotationToCursor(float DeltaTime)
{
	if(!GetCharacter() || !GetCharacter()->GetCharacterMovement())
		return;

	// rotate character to cursor only if is moving
	GetCharacter()->GetCharacterMovement()->bUseControllerDesiredRotation = GetCharacter()->GetVelocity().Size() > 0.0f;
	
	FHitResult Result;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Result);
	if(Result.bBlockingHit)
	{
		// calculate rotation from character to cursor
		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetCharacter()->GetActorLocation(), Result.Location);
		NewRotation.Roll = NewRotation.Pitch = 0.0f;
		SetControlRotation(NewRotation);
		UpdateRotation(DeltaTime);
	}
}

void ABrainHackerPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// bind input to automatically trigger ability
	BindAbilitiesDirectInput();
}

void ABrainHackerPlayerController::BindAbilitiesDirectInput()
{
	ABrainHackerCharacter* BrainHackerCharacter = Cast<ABrainHackerCharacter>(GetCharacter());
	ensureMsgf(BrainHackerCharacter, TEXT("ABrainHackerPlayerController cant find character!"));
	BrainHackerCharacter->GetAbilitySystemComponent()->BindAbilityActivationToInputComponent(InputComponent,
	FGameplayAbilityInputBinds(FString("Confirm"),
	FString("Cancel"), FString("EBHAbilityInputID"),
	static_cast<int32>(EBHAbilityInputID::Confirm), static_cast<int32>(EBHAbilityInputID::Cancel)));
}
