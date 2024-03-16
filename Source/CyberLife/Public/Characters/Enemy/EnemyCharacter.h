// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "Components/CombatComponentInterface.h"
#include "Controllers/AI/PatrolerInterface.h"
#include "EnemyCharacter.generated.h"

class UCombatComponent;
/**
 * 
 */
UCLASS()
class CYBERLIFE_API AEnemyCharacter : public ACharacterBase, public IPatrolerInterface, public ICombatComponentInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	
	virtual  float SetMovementMode_Implementation(const EEnemyMovementMode InMovementMode) override;

	virtual UCombatComponent* GetCombatComponent_Implementation() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UCombatComponent> CombatComponent;
};