// Mamont Protaction copy rights


#include "Components/WeaponCombatComponent.h"

#include "Items/InventoryComponent.h"
#include "Items/InventoryComponentInterface.h"
#include "Items/Weapon.h"

class AWeapon;

void UWeaponCombatComponent::StartAttack()
{
	if(const TObjectPtr<AWeapon> Weapon = IInventoryComponentInterface::Execute_GetInventoryComponent(GetOwner())->GetWeapon(); IsValid(Weapon))
	{
		Weapon->StartAttack_Implementation();
	}
	else
	{
		Super::StartAttack();
	}
}

void UWeaponCombatComponent::EndAttack()
{
	if(const TObjectPtr<AWeapon> Weapon = IInventoryComponentInterface::Execute_GetInventoryComponent(GetOwner())->GetWeapon(); IsValid(Weapon))
	{
		Weapon->EndAttack_Implementation();
	}
	else
	{
		Super::EndAttack();
	}
	
}