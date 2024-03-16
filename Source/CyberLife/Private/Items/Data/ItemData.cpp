// Mamont Protaction copy rights


#include "Items/Data/ItemData.h"

FIntPoint UItemData::GetDimensions() const
{
	if(bIsRotated)
	{
		return {Dimensions.Y, Dimensions.X};
	}
	return Dimensions;
}

UMaterialInterface* UItemData::GetIcon() const
{
	if(bIsRotated) return IconRotated;

	return Icon;
}

void UItemData::Rotate()
{
	bIsRotated = !bIsRotated;
}

void UItemData::EquipWeapon()
{
	bEquiped = true;
}

void UItemData::UnEquipWeapon()
{
	bEquiped = false;
}

FPrimaryAssetId UItemData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, GetFName());
}
