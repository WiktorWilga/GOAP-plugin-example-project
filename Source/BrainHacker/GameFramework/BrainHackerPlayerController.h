// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BrainHackerPlayerController.generated.h"

/**
 * Base PlayerController for playable character
 */
UCLASS()
class ABrainHackerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	ABrainHackerPlayerController();

protected:

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	/** Movement */
	void OnMoveForward(const float Value);
	void OnMoveRight(const float Value);

	/** Rotate controlled character to cursor. Need be called in each frame */
	void UpdateCharacterRotationToCursor(const float DeltaTime);

protected:

	virtual void OnPossess(APawn* InPawn) override;

private:

	/** Bind input defined in EGDAbilityInputID to automatically activate ability */
	void BindAbilitiesDirectInput();
};

