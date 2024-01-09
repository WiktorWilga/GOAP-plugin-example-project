// Copyright Wiktor Wilga (wilgawiktor@gmail.com)


#include "BHAIController.h"

#include "GOAPMemoryComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ABHAIController::ABHAIController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	// configure sight for AIPerception
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	SightConfig->SightRadius = 1500.0f;
	SightConfig->LoseSightRadius = 1500.0f;
	SightConfig->PeripheralVisionAngleDegrees = 60.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->SetMaxAge(60.0f);
	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());
}

void ABHAIController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	// call OnTargetPerceptionUpdated each time when has signal from PawnSensing
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ABHAIController::OnTargetPerceptionUpdated);
	// controlled character must has memory component
	ControlledPawnMemory = Cast<UGOAPMemoryComponent>(NewPawn->GetComponentByClass(UGOAPMemoryComponent::StaticClass()));
	if(!ControlledPawnMemory)
		UE_LOG(LogTemp, Error, TEXT("Pawn (%s) controlled by ABHAIController must has memory component!"), *NewPawn->GetName());
}
void ABHAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(Actor && ControlledPawnMemory && Stimulus.WasSuccessfullySensed())
	{
		ControlledPawnMemory->RegisterActorInMemory(Actor);
	}
}
