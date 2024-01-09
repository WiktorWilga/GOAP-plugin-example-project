// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#include "BrainHackerGameMode.h"

#include "BHHUD.h"
#include "BrainHackerCharacter.h"
#include "Kismet/GameplayStatics.h"

ABrainHackerGameMode::ABrainHackerGameMode()
{
}

void ABrainHackerGameMode::BeginPlay()
{
	Super::BeginPlay();

	const auto PlayerCharacter = Cast<ABrainHackerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	ensureMsgf(PlayerCharacter, TEXT("Cant find player character!"));
	PlayerCharacter->OnCharacterDiedDelegate.AddDynamic(this, &ABrainHackerGameMode::OnPlayerCharacterDied);
}

void ABrainHackerGameMode::RestartGame()
{
	UGameplayStatics::OpenLevel(this, *UGameplayStatics::GetCurrentLevelName(GetWorld()), true);
}

void ABrainHackerGameMode::OnPlayerCharacterDied(ABrainHackerCharacter* Character)
{
	const auto HUD = Cast<ABHHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	ensureMsgf(HUD, TEXT("Cant find HUD!"));
	HUD->ShowGameOverScreen();
	// GetWorld()->GetFirstPlayerController()->SetPause(true);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.5);
}
