// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Abilities/GameplayAbilityBase.h"
#include "FlashlightAbility.generated.h"

/**
 * 
 */
UCLASS()
class CYBERLIFE_API UFlashlightAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Flashlight")
	float Intensity{0.f};
	UPROPERTY(EditDefaultsOnly, Category="Flashlight")
	TObjectPtr<USoundBase> FlashlightSound{nullptr};
	
};