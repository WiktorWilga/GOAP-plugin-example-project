// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#include "BrainHackerCharacter.h"

#include "BHCharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GOAPWorldStateProvider.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

ABrainHackerCharacter::ABrainHackerCharacter(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UBHCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// World state data provider (AI - GOAP)
	GOAPWorldStateProvider = CreateDefaultSubobject<UGOAPWorldStateProvider>(TEXT("GOAPWorldStateProvider"));

	// GAS init
	AbilitySystemComponent = CreateDefaultSubobject<UBHAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UBHAttributeSetBase>(TEXT("AttributeSet"));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABrainHackerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// set owner actor and avatar actor for ability system comp
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	// grand abilities
	AddCharacterAbilities();
	// bind attributes changed events
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ABrainHackerCharacter::OnHealthChanged);
}

void ABrainHackerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// init attribute set with values set in data table
	ensureMsgf(AttributesDataTable && AbilitySystemComponent, TEXT("Cant init character attribute set for %s!"), *this->GetName());
	AbilitySystemComponent->InitStats(UBHAttributeSetBase::StaticClass(), AttributesDataTable);
}

void ABrainHackerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABrainHackerCharacter::AddCharacterAbilities()
{
	for (auto Ability : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1,
			static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));
	}
}

void ABrainHackerCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Log, TEXT("Current health [%s]: %f"), *this->GetName(), Data.NewValue);
	OnHealthChangedDelegate.Broadcast(this, Data.OldValue, Data.NewValue);
	if(Data.NewValue <= 0.0f)
	{
		Die();
	}
}

void ABrainHackerCharacter::Die()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetSimulatePhysics(true);
	Controller->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	OnCharacterDiedDelegate.Broadcast(this);
}
