// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Abilities/GameplayAbilityBase.h"
#include "SprintAbility.generated.h"

/**
 * 
 */
UCLASS()
class CYBERLIFE_API USprintAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle,
	                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

private:
	void SetMovementSpeed(const FGameplayAttribute& GameplayAttribute) const;
};
