// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BrainHackerGameMode.generated.h"

/**
 * Base GameMode for gameplay
 */
UCLASS(minimalapi)
class ABrainHackerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	ABrainHackerGameMode();

	virtual void BeginPlay() override;

	/** Reloads level and starts game. */
	UFUNCTION(BlueprintCallable)
	void RestartGame();

private:
	
	UFUNCTION()
	void OnPlayerCharacterDied(class ABrainHackerCharacter* Character);
};



