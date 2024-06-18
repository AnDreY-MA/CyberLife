// Mamont Protaction copy rights


#include "Abilities/Abilities/Combat/AttackAbilityBase.h"

#include "Components/InteractionComponent.h"
#include "Components/InteractionComponentInterface.h"

bool UAttackAbilityBase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                            const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if(auto* Avatar{ActorInfo->AvatarActor.Get()}; Avatar->Implements<UInteractionComponentInterface>())
	{
		if(auto* InteractionComponent = IInteractionComponentInterface::Execute_GetInteractionComponent(Avatar); InteractionComponent &&
		InteractionComponent->IsHoldingObject())
		{
			InteractionComponent->ThrowObject();
			return false;
		}
		
	}
	
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}