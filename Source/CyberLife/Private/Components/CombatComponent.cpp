// Fill out your copyright notice in the Description page of Project Settings.


#include "Components//CombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"

#include "Kismet/KismetSystemLibrary.h"

UCombatComponent::UCombatComponent()
	: AttackHandSocket("HandAttackSocket")
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UCombatComponent::StartAttack()
{
	if(const auto* OwnerMesh{GetOwner()->FindComponentByClass<USkeletalMeshComponent>()}; OwnerMesh)
	{
		FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &UCombatComponent::TraceAttack, OwnerMesh);
		GetWorld()->GetTimerManager().SetTimer(AttackTimer, Delegate, 0.05f, true);
	}
}

void UCombatComponent::EndAttack()
{
	GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
}

void UCombatComponent::TraceAttack(const USkeletalMeshComponent* InOwnerMesh)
{
	const FVector InLocation{InOwnerMesh->GetSocketLocation(AttackHandSocket)};
	FHitResult HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> InObjectTypes{ObjectTypeQuery1, ObjectTypeQuery2, ObjectTypeQuery3, ObjectTypeQuery3, ObjectTypeQuery4,
	ObjectTypeQuery5, ObjectTypeQuery5};
	if(UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), InLocation, InLocation, AttackRadius, InObjectTypes, true, {GetOwner()},
	                                                     EDrawDebugTrace::ForDuration, HitResult, true))
	{
		if(auto* HitActor {HitResult.GetActor()}; HitActor)
		{
			FGameplayEventData Payload;
			Payload.Instigator = GetOwner()->GetInstigatorController();
			Payload.Target = HitActor;
			Payload.TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(HitActor);
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner()->GetInstigatorController(), DamageTag, Payload);
		}
	}
}
