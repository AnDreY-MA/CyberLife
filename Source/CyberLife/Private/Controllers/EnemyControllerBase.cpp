// Mamont Protaction copy rights


#include "Controllers/EnemyControllerBase.h"

#include "Abilities/Attributes/CharacterAttributeSet.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Channels/MovieSceneDoubleChannel.h"
#include "Controllers/AI/AISenseState.h"
#include "Controllers/AI/AIState.h"
#include "Engine/DamageEvents.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

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

void AEnemyControllerBase::BeginPlay()
{
	Super::BeginPlay();

	auto* Attribute{AbilityComponent->GetSet<UCharacterAttributeSet>()};
	Attribute->OnHealthChanged.AddDynamic(this, &AEnemyControllerBase::OnHealthChange);
}

EAIState AEnemyControllerBase::GetCurrentState() const
{
	return static_cast<EAIState>(Blackboard->GetValueAsEnum(StateKeyName));
}

void AEnemyControllerBase::HandleSensedSound(const FVector& InLocation)
{
	if(const EAIState CurrentState{GetCurrentState()};
		CurrentState == EAIState::Passive || CurrentState == EAIState::Investigating)
	{
		SetStateAsInvestigating(InLocation);
	}
}

void AEnemyControllerBase::HandleSensedSight(AActor* InTarget)
{
	if(const EAIState CurrentState{GetCurrentState()};
		CurrentState == EAIState::Passive || CurrentState == EAIState::Investigating)
	{
		SetStateAsAttacking(InTarget);
	}
	
}

bool AEnemyControllerBase::CanSenseActor(AActor* InActor, const EAISenseState InState, FAIStimulus& OutStimulus)
{
	TMap<EAISenseState, TSubclassOf<UAISense>> AISenses{
		{EAISenseState::None, nullptr},
	{EAISenseState::Sight, UAISense_Sight::StaticClass()},
	{EAISenseState::Damaging, UAISense_Damage::StaticClass()},
	{EAISenseState::Hearing, UAISense_Hearing::StaticClass()}};
	FActorPerceptionBlueprintInfo PerceptionInfo;
	PerceptionComponent->GetActorsPerception(InActor, PerceptionInfo);
	for(auto Stimul : PerceptionInfo.LastSensedStimuli)
	{
		const TSubclassOf<UAISense> SenseClass {UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimul)};

		if(SenseClass == *AISenses.Find(InState))
		{
			OutStimulus = Stimul;
			return Stimul.WasSuccessfullySensed();
		}
	}
	
	return false;
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

void AEnemyControllerBase::OnHealthChange(float NewValue, float OldValue, float Magintude)
{
	//UAISense_Damage::ReportDamageEvent(GetWorld(), )
	if(NewValue <= 0.0f)
	{
		GetPawn()->Destroy();
	}

}