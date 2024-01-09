// Copyright Wiktor Wilga (wilgawiktor@gmail.com)


#include "BHTargetingComponent.h"

UBHTargetingComponent::UBHTargetingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBHTargetingComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ABrainHackerCharacter>(GetOwner());
	ensureMsgf(Character, TEXT("BHTargetingComponent can exists only in ABrainHackerCharacter!"));
	OwnerAbilitySystemComponent = Cast<UBHAbilitySystemComponent>(Character->GetAbilitySystemComponent());
	ensureMsgf(OwnerAbilitySystemComponent, TEXT("BHTargetingComponent owner need to has UBHAbilitySystemComponent!"));
	PlayerController = Cast<APlayerController>(Character->GetController());
	ensureMsgf(PlayerController, TEXT("Owner of BHTargetingComponent must be controlled by player controller!"));

	InitializeAvailableHacks();
	ensureMsgf(AvailableHacks.Num() > 0, TEXT("There isn't any hack available for BHTargetingComponent owner!"));
	SelectedHackIndex = 0;
}

void UBHTargetingComponent::InitializeAvailableHacks()
{
	for(auto Ability : OwnerAbilitySystemComponent->GetActivatableAbilitiesBP())
	{
		if(auto Hack = Cast<UBHHackAbility>(Ability))
		{
			AvailableHacks.Add(Hack);
		}
	}
}

bool UBHTargetingComponent::CheckIsInRange(const AActor* Actor) const
{
	return FVector::Distance(Character->GetActorLocation(), Actor->GetActorLocation()) < AvailableHacks[SelectedHackIndex]->GetHackRange();
}

bool UBHTargetingComponent::IsTargetingLocked() const
{
	for(auto Ability : OwnerAbilitySystemComponent->GetActiveAbilities())
	{
		if(Cast<UBHHackAbility>(Ability))
		{
			return true;
		}
	}
	return false;
}

void UBHTargetingComponent::SelectNextHack()
{
	if(IsTargetingLocked())
		return;
	
	SelectedHackIndex = (SelectedHackIndex + 1) % AvailableHacks.Num();
	OnSelectedHackChangedDelegate.Broadcast(AvailableHacks[SelectedHackIndex]);
	OnHackSelected(AvailableHacks[SelectedHackIndex]);
}

void UBHTargetingComponent::SelectPreviousHack()
{
	if(IsTargetingLocked())
		return;
	
	SelectedHackIndex = (SelectedHackIndex == 0) ? (AvailableHacks.Num() - 1) : (SelectedHackIndex - 1);
	OnSelectedHackChangedDelegate.Broadcast(AvailableHacks[SelectedHackIndex]);
	OnHackSelected(AvailableHacks[SelectedHackIndex]);
}

void UBHTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// update target under cursor
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(CollisionChannel, false, HitResult);
	if(HitResult.GetActor() && (HitResult.GetActor()->GetClass() == TargetClass ||
		HitResult.GetActor()->GetClass()->IsChildOf(TargetClass)))
	{
		if(SelectedTarget)
		{
			if(HitResult.GetActor() != SelectedTarget)
			{
				if(CheckIsInRange(HitResult.GetActor()) && !IsTargetingLocked())
				{
					// replace previous target
					OnTargetUnselected(SelectedTarget);
					SelectedTarget = HitResult.GetActor();
					OnTargetSelected(SelectedTarget);
					OnSelectedTargetChangedDelegate.Broadcast(SelectedTarget);
				}
			}
		}
		else
		{
			SelectedTarget = HitResult.GetActor();
			OnTargetSelected(SelectedTarget);
			OnSelectedTargetChangedDelegate.Broadcast(SelectedTarget);
		}
	}
	// unselect target if current is too far
	if(SelectedTarget)
	{
		if(!CheckIsInRange(SelectedTarget))
		{
			OnTargetUnselected(SelectedTarget);
			SelectedTarget = nullptr;
			OnSelectedTargetChangedDelegate.Broadcast(SelectedTarget);
		}
	}
}

