#pragma once

#include "CoreMinimal.h"
#include "Items/Weapon.h"
#include "FireWeapon.generated.h"

class ABullet;

UCLASS(Blueprintable)
class CYBERLIFE_API AFireWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void Attack(AActor* OwnerActor) override;

private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	TSubclassOf<ABullet> BulletClass;

protected:
	virtual void BeginPlay() override;
	
};
