// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "Components/CombatComponent.h"
#include "WeaponCombatComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(CombatComponents), meta=(BlueprintSpawnableComponent))
class CYBERLIFE_API UWeaponCombatComponent : public UCombatComponent
{
	GENERATED_BODY()

public:
	virtual void StartAttack() override;
	virtual void EndAttack() override;
	
};
