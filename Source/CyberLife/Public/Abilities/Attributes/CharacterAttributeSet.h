// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CharacterAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChanged, float, NewValue, float, OldValue, float, Magintude);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStaminaChanged, float, NewValue, float, OldValue, float, Magintude);

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS(Blueprintable, BlueprintType)
class CYBERLIFE_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	mutable FOnHealthChanged OnHealthChanged;
	mutable FOnStaminaChanged OnStaminaChanged;

	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Health)

	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Damage)
	
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Stamina)
	
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxStamina)
	
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, SprintSpeed)
	
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, WalkSpeed)

protected:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Health", meta=(AllowPrivateAccess="true"))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Stamina", meta=(AllowPrivateAccess="true"))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Damage", meta=(AllowPrivateAccess="true"))
	FGameplayAttributeData Damage;
	
	UPROPERTY(BlueprintReadOnly, Category = "Stamina", meta=(AllowPrivateAccess="true"))
	FGameplayAttributeData Stamina;

	UPROPERTY(BlueprintReadOnly, Category = "Stamina", meta=(AllowPrivateAccess="true"))
	FGameplayAttributeData MaxStamina;

	UPROPERTY(BlueprintReadOnly, Category = "Speed|Sprint", meta=(AllowPrivateAccess="true"))
	FGameplayAttributeData SprintSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Speed|Walk", meta=(AllowPrivateAccess="true"))
	FGameplayAttributeData WalkSpeed;
	
};