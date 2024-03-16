// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(CombatComponents), meta=(BlueprintSpawnableComponent) )
class CYBERLIFE_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();

	virtual void StartAttack();
	virtual void EndAttack();

	UAnimMontage* GetAttackMontage() const { return MeeleAttackAnim; }

private:

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	FGameplayTag DamageTag;

	UPROPERTY(EditDefaultsOnly, Category="Combat|Hands")
	FName AttackHandSocket;
	UPROPERTY(EditDefaultsOnly, Category="Combat|Hands")
	float AttackRadius{20.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Animation", meta=(AllowPrivateAccess))
	TObjectPtr<UAnimMontage> MeeleAttackAnim;

	UPROPERTY()
	FTimerHandle AttackTimer;
	UPROPERTY()
	FVector TraceLocation;
	
    UFUNCTION()
	void TraceAttack(const USkeletalMeshComponent* InOwnerMesh);
	
};