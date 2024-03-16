// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AIController.h"
#include "EnemyControllerInterface.h"
#include "Abilities/Component/AbilityComponentBase.h"
#include "EnemyControllerBase.generated.h"


UCLASS()
class CYBERLIFE_API AEnemyControllerBase : public AAIController, public IAbilitySystemInterface, public IEnemyControllerInterface
{
	GENERATED_BODY()

public:
	AEnemyControllerBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void Attack_Implementation() override;

	virtual AActor* GetAttackTarget_Implementation() const override;
	
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Ability", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UAIPerceptionComponent> EnemyPerceptionComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Ability", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UAbilityComponentBase> AbilityComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BehaviorTree", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BehaviorTree|KeyNames", meta=(AllowPrivateAccess="true"))
	FName AttackTargetKeyName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BehaviorTree|KeyNames", meta=(AllowPrivateAccess="true"))
	FName StateKeyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BehaviorTree|KeyNames", meta=(AllowPrivateAccess="true"))
	FName PointOfInterestKeyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BehaviorTree|KeyNames", meta=(AllowPrivateAccess="true"))
	FName AttackRadiusKeyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BehaviorTree|KeyNames", meta=(AllowPrivateAccess="true"))
	FName DefendRadiusKeyName;

	UPROPERTY()
	TObjectPtr<AActor> TargetActor;

	UFUNCTION(BlueprintCallable, Category="States")
	void SetStateAsPassive();

	UFUNCTION(BlueprintCallable, Category="States")
	void SetStateAsAttacking(AActor* Target);

	UFUNCTION(BlueprintCallable, Category="States")
	void SetStateAsInvestigating(const FVector& InLocation);
	
};