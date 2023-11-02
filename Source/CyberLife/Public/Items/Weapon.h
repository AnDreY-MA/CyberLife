#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

UCLASS()
class CYBERLIFE_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	AWeapon();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon", meta=(AllowPrivateAccess))
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon", meta=(AllowPrivateAccess))
	float DamagePower;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* AttackSound;
	
	virtual void BeginPlay() override;

public:
	virtual void Interact(UInteractionComponent* InteractionComponent) override;
	
	virtual void Attack(AActor* OwnerActor);
	
	void Equip();
	void UnEquip();

protected:
	virtual void ShowOutline() override;
	virtual void HideOutline() override;
	
};