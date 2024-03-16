// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Abilities/GameplayAbilityBase.h"
#include "AttackAbility.generated.h"

/**
 * 
 */
UCLASS()
class CYBERLIFE_API UAttackAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void OnDamageEvent(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData);

private:
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSoftClassPtr<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Settings|Damage")
	FGameplayTagContainer DamageEvent;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Damage")
	FGameplayTag HitAbilityTag;

	UPROPERTY()
	TSet<const AActor*> DamageActors;

	void LoadEffect(const FGameplayAbilityTargetDataHandle& TargetData);

	void AppleDamageEffect(FGameplayAbilityTargetDataHandle TargetData) const;

};
