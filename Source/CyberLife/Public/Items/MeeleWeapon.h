#pragma once

#include "CoreMinimal.h"
#include "Items/Weapon.h"
#include "MeeleWeapon.generated.h"

UCLASS(Blueprintable)
class CYBERLIFE_API AMeeleWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:
	virtual void Attack(AActor* OwnerActor) override;

	UFUNCTION(BlueprintImplementableEvent)
	void TriggerWaepon();

	UFUNCTION(BlueprintCallable)
	void TriggerAttack();
	UFUNCTION(BlueprintCallable)
	void StopTrigger();

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle TimerHandle;
	
	void OnAttack();
	

};