// Mamont Protaction copy rights


#include "Characters/Enemy/EnemyCharacter.h"

#include "Components/CombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	CombatComponent = CreateDefaultSubobject<UCombatComponent>("CombatComponent");
}

float AEnemyCharacter::SetMovementMode_Implementation(const EEnemyMovementMode InMovementMode)
{
	TMap<EEnemyMovementMode, float> SpeedValues{
	{EEnemyMovementMode::Idle, 0.0f}, {EEnemyMovementMode::Walk, 100.f},
	{EEnemyMovementMode::Jogging, 300.f}, {EEnemyMovementMode::Run, 500.f}};
	
	const float Speed = SpeedValues.FindAndRemoveChecked(InMovementMode);
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	return Speed;
}

UCombatComponent* AEnemyCharacter::GetCombatComponent_Implementation()
{
	return CombatComponent.Get();
}