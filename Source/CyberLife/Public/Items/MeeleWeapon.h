#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Items/Weapon.h"
#include "MeeleWeapon.generated.h"


UCLASS(Blueprintable)
class CYBERLIFE_API AMeeleWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:
	virtual void Attack(AActor* OwnerActor) override;

	virtual void StartAttack_Implementation() override;
	virtual void EndAttack_Implementation() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FGameplayTag DamageTag;
	
	FTimerHandle TimerHandle;
	
	void OnAttack();
	

};