// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BHAIController.generated.h"

/**
 * Base AI controller for all NPC
 */
UCLASS()
class BRAINHACKER_API ABHAIController : public AAIController
{
	GENERATED_BODY()

public:

	ABHAIController();
	
	virtual void OnPossess(APawn* NewPawn) override;

protected:

	/** AI perception for NPCs sight */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAIPerceptionComponent* AIPerception;

private:

	/** Called when AIPerception see any pawn */
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	/** Reference to memory component of currently controlled character */
	UPROPERTY()
	class UGOAPMemoryComponent* ControlledPawnMemory = nullptr;
	
};