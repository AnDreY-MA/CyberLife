// Mamont Protaction copy rights


#include "Abilities/Abilities/SprintAbility.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Attributes/CharacterAttributeSet.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void USprintAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	SetMovementSpeed(UCharacterAttributeSet::GetSprintSpeedAttribute());
}

void USprintAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
	
}

void USprintAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	SetMovementSpeed(UCharacterAttributeSet::GetWalkSpeedAttribute());

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
}

void USprintAbility::SetMovementSpeed(const FGameplayAttribute& GameplayAttribute) const
{
	const float CurrentValue = CurrentActorInfo->AbilitySystemComponent.Get()->GetNumericAttribute(GameplayAttribute);
	CurrentActorInfo->AvatarActor.Get()->GetInstigatorController()->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = CurrentValue;

}
