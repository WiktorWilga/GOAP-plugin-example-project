// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "BrainHacker/GAS/BHAbilitySystemComponent.h"
#include "BrainHacker/GAS/BHAttributeSetBase.h"
#include "BrainHacker/GAS/BHGameplayAbility.h"
#include "BrainHackerCharacter.generated.h"

class ABrainHackerCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthChangedDelegate, ABrainHackerCharacter*, Character, float, OldValue, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ABrainHackerCharacter*, Character);

/**
 * Base class for all characters in game
 */
UCLASS(Blueprintable)
class ABrainHackerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	ABrainHackerCharacter(const class FObjectInitializer& ObjectInitializer);

	/** Called when character's health changed. */
	UPROPERTY(BlueprintAssignable)
	FHealthChangedDelegate OnHealthChangedDelegate;
	/** Called when character died (heath has dropped to zero). */
	UPROPERTY(BlueprintAssignable)
	FCharacterDiedDelegate OnCharacterDiedDelegate;

	virtual void PossessedBy(AController * NewController) override;
	virtual void Tick(float DeltaSeconds) override;

	// Start IAbilitySystemInterface implementation
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	// End IAbilitySystemInterface implementation

	/** Return character attribute set */
	UBHAttributeSetBase* GetAttributeSet() const { return AttributeSet; }

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:

	virtual void BeginPlay() override;
	
	/** For Gameplay Ability System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBHAbilitySystemComponent* AbilitySystemComponent;
	/** Characters attributes */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBHAttributeSetBase* AttributeSet;

	/** Called when health attribute from AttributeSet is changed. */
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);

	/** Disable control of this character and make other visual work. */
	void Die();

private:
	
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Character adds some data to world state for AI planner and be considered in planning  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	class UGOAPWorldStateProvider* GOAPWorldStateProvider;

	/** Initial values of attributes which will be set in characters AttributeSet */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	UDataTable* AttributesDataTable;

	/** Abilities granted to character at start */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UBHGameplayAbility>> CharacterAbilities;
	
	/** Give all abilities defined in CharacterAbilities */
	void AddCharacterAbilities();
};

