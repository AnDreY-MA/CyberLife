#include "Items/ItemObject.h"

UItemObject::UItemObject() :
	bEquiped(false),
	bIsRotated(false)
{
}

void UItemObject::EquipWeapon()
{
	bEquiped = true;
}

void UItemObject::UnEquipWeapon()
{
	bEquiped = false;
}

FIntPoint UItemObject::GetDimensions() const
{
	if(bIsRotated)
	{
		return {Dimensions.Y, Dimensions.X};
	}
	return Dimensions;
}

UMaterialInterface* UItemObject::GetIcon() const
{
	if(bIsRotated) return IconRotated;

	return Icon;
}

void UItemObject::Rotate()
{
	bIsRotated = !bIsRotated;
}