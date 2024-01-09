// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BHAttributeSetBase.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * Base attributes for characters. Currently used for each type of character (player controlled and enemies), so some
 * attributes isn't used in some classes. Can be inherited to be more suitable to specified class.
 */
UCLASS()
class BRAINHACKER_API UBHAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:

	UBHAttributeSetBase();

	/** Function to respond to changes on CurrentValue before change happens */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	/** Function called after change BaseValue */
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBHAttributeSetBase, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Energy")
	FGameplayAttributeData Energy;
	ATTRIBUTE_ACCESSORS(UBHAttributeSetBase, Energy)

	UPROPERTY(BlueprintReadOnly, Category = "Fear")
	FGameplayAttributeData Fear;
	ATTRIBUTE_ACCESSORS(UBHAttributeSetBase, Fear)

	UPROPERTY(BlueprintReadOnly, Category = "RunSpeed")
	FGameplayAttributeData RunSpeed;
	ATTRIBUTE_ACCESSORS(UBHAttributeSetBase, RunSpeed)

	UPROPERTY(BlueprintReadOnly, Category = "WalkSpeed")
	FGameplayAttributeData WalkSpeed;
	ATTRIBUTE_ACCESSORS(UBHAttributeSetBase, WalkSpeed)

	UPROPERTY(BlueprintReadOnly, Category = "CrouchSpeed")
	FGameplayAttributeData CrouchSpeed;
	ATTRIBUTE_ACCESSORS(UBHAttributeSetBase, CrouchSpeed)

	UPROPERTY(BlueprintReadOnly, Category = "AttackDamage")
	FGameplayAttributeData AttackDamage;
	ATTRIBUTE_ACCESSORS(UBHAttributeSetBase, AttackDamage)
};
