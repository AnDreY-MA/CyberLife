// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "Items/Data/ItemData.h"
#include "WeaponData.generated.h"

/**
 * 
 */
UCLASS()
class CYBERLIFE_API UWeaponData : public UItemData
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float Damage;

	friend class AWeapon;
	
};
