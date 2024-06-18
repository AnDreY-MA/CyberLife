// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Abilities/GameplayAbilityBase.h"
#include "AttackAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class CYBERLIFE_API UAttackAbilityBase : public UGameplayAbilityBase
{
	GENERATED_BODY()

protected:

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	
};
