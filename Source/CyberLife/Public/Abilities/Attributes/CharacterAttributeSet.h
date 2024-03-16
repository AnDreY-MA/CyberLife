// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CharacterAttributeSet.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnHealthChanged, float NewValue, float OldValue, float Magintude);

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
	FOnHealthChanged OnHealthChanged;

	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Health)

	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Damage)

protected:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Health", meta=(AllowPrivateAccess="true"))
	FGameplayAttributeData Health;
	

	UPROPERTY(BlueprintReadOnly, Category = "Damage", meta=(AllowPrivateAccess="true"))
	FGameplayAttributeData Damage;
	
};
