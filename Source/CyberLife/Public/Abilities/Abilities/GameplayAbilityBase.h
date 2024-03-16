// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AbilityInputID.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class CYBERLIFE_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:

	EAbilityInputID GetAbilityID() const { return InputID; }

private:

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	EAbilityInputID InputID{EAbilityInputID::None};
};