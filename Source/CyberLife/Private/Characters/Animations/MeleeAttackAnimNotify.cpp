// Mamont Protaction copy rights


#include "Characters/Animations/MeleeAttackAnimNotify.h"

#include "Components/CombatComponent.h"
#include "Components/CombatComponentInterface.h"

void UMeleeAttackAnimNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                         float TotalDuration)
{
	if(auto* Owner{MeshComp->GetOwner()}; Owner && Owner->Implements<UCombatComponentInterface>())
	{
		if(auto* CombatComponent = ICombatComponentInterface::Execute_GetCombatComponent(Owner); CombatComponent)
		{
			CombatComponent->StartAttack();
		}
	}
}

void UMeleeAttackAnimNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(auto* Owner{MeshComp->GetOwner()}; Owner && Owner->Implements<UCombatComponentInterface>())
	{
		if(auto* CombatComponent = ICombatComponentInterface::Execute_GetCombatComponent(Owner); CombatComponent)
		{
			CombatComponent->EndAttack();
		}
	}
}