// Mamont Protaction copy rights


#include "Controllers/EnemyControllerBase.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Controllers/AI/AIState.h"
#include "Perception/AIPerceptionComponent.h"

AEnemyControllerBase::AEnemyControllerBase()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponentBase>("AbilityComponent");

	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("EnemyPerceptionComponent");
}

UAbilitySystemComponent* AEnemyControllerBase::GetAbilitySystemComponent() const
{
	return AbilityComponent;
}

void AEnemyControllerBase::Attack_Implementation()
{
	AbilityComponent->ActivateAbility(EAbilityInputID::Attack);
}

AActor* AEnemyControllerBase::GetAttackTarget_Implementation() const
{
	return TargetActor.Get();
}

void AEnemyControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	AbilityComponent->InitAbilityActorInfo(this, InPawn);

	RunBehaviorTree(BehaviorTree);

	SetStateAsPassive();

	Blackboard->SetValueAsFloat(AttackRadiusKeyName, 10.f);
	Blackboard->SetValueAsFloat(DefendRadiusKeyName, 250.f);
}

void AEnemyControllerBase::SetStateAsPassive()
{
	Blackboard->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAIState::Passive));
}

void AEnemyControllerBase::SetStateAsAttacking(AActor* Target)
{
	Blackboard->SetValueAsObject(AttackTargetKeyName, Target);
	Blackboard->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAIState::Attacking));
	TargetActor = Target;
}

void AEnemyControllerBase::SetStateAsInvestigating(const FVector& InLocation)
{
	Blackboard->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAIState::Investigating));
	Blackboard->SetValueAsVector(PointOfInterestKeyName, InLocation);
}