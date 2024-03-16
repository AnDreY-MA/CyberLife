// Mamont Protaction copy rights


#include "Abilities/Abilities/Combat/AttackAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Abilities/Tasks/PlayMontageAndWaitForEvent.h"
#include "Components/CombatComponent.h"
#include "Components/CombatComponentInterface.h"
#include "Components/InteractionComponent.h"
#include "Components/InteractionComponentInterface.h"
#include "Engine/AssetManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogAttackAbility, All, All);

void UAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     const FGameplayEventData* TriggerEventData)
{
	auto* Avatar{ActorInfo->AvatarActor.Get()};
	if(Avatar->Implements<UInteractionComponentInterface>())
	{
		if(auto* InteractionComponent = IInteractionComponentInterface::Execute_GetInteractionComponent(Avatar); InteractionComponent &&
		InteractionComponent->IsHoldingObject())
		{
			InteractionComponent->ThrowObject();
			EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
			return;
		}
		
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UE_LOG(LogTemp, Warning, TEXT("ATTACK"));

	if(Avatar->Implements<UCombatComponentInterface>())
	{
		UE_LOG(LogTemp, Warning, TEXT("IN"));

		const auto* CombatComponent = ICombatComponentInterface::Execute_GetCombatComponent(Avatar);
		if(!CombatComponent)
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
			return;
		}
		auto* AttackMontage = CombatComponent->GetAttackMontage();
		if(!AttackMontage)
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
			return;
		}
		UE_LOG(LogTemp, Warning, TEXT("Cont"));

		auto* NewTask = UPlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(this, NAME_None, AttackMontage, DamageEvent);
		NewTask->OnCompleted.AddDynamic(this, &UAttackAbility::OnCompleted);
		NewTask->OnBlendOut.AddDynamic(this, &UAttackAbility::OnCompleted);
		NewTask->OnInterrupted.AddDynamic(this, &UAttackAbility::OnCompleted);
		NewTask->EventReceived.AddDynamic(this, &UAttackAbility::OnDamageEvent);
		NewTask->ReadyForActivation();
	}
	
}

void UAttackAbility::OnDamageEvent(FGameplayTag EventTag, FGameplayEventData EventData)
{
	const auto* DamageActor = EventData.Target.Get();
	if(DamageActors.Contains(DamageActor)) return;

	DamageActors.Add(DamageActor);
	if(DamageActor->Implements<UAbilitySystemInterface>())
	{
		auto* AbilityComponentDamager{Cast<IAbilitySystemInterface>(DamageActor)->GetAbilitySystemComponent()};
		AbilityComponentDamager->TryActivateAbilitiesByTag(FGameplayTagContainer{HitAbilityTag});
		LoadEffect(EventData.TargetData);
	}
	
}

void UAttackAbility::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);

}

void UAttackAbility::LoadEffect(const FGameplayAbilityTargetDataHandle& TargetData)
{
	auto& StreamManager{UAssetManager::GetStreamableManager()};
	FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &UAttackAbility::AppleDamageEffect, TargetData);
	StreamManager.RequestAsyncLoad(DamageEffectClass.ToString(), Delegate);
}

void UAttackAbility::AppleDamageEffect(FGameplayAbilityTargetDataHandle TargetData) const
{
	(void)ApplyGameplayEffectToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, TargetData, DamageEffectClass.Get(), 1);

}
