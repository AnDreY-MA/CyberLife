#pragma once

#include "CoreMinimal.h"
#include "WeaponInterface.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

UCLASS()
class CYBERLIFE_API AWeapon : public AItem, public IWeaponInterface
{
	GENERATED_BODY()

public:
	AWeapon();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon", meta=(AllowPrivateAccess))
	float DamagePower;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* AttackSound;
	
	virtual void BeginPlay() override;

public:
	virtual void Interact_Implementation(UInteractionComponent* InteractionComponent) override;
	
	virtual void Attack(AActor* OwnerActor);
	
	void Equip();
	void UnEquip();
	
};