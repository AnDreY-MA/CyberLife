#include "Items/InventoryComponent.h"

#include "Items/ItemObject.h"
#include "UI/GridElements.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Items.SetNum(Columns * Rows);
}

void UInventoryComponent::ForEachIndex(UItemObject* ItemObject, int32 TopLeftIndex, FTile& Tile)
{
	const int32 XFirstIndex = IndexToTile(TopLeftIndex).X;
	const int32 XLastIndex = XFirstIndex + (ItemObject->GetDimensions().X - 1);
	const int32 YFirstIndex = IndexToTile(TopLeftIndex).Y;
	const int32 YLastIndex = YFirstIndex + (ItemObject->GetDimensions().Y - 1);

	for	(int32 XIndex = XFirstIndex; XIndex < XLastIndex; ++XIndex)
	{
		for (int32 YIndex = YFirstIndex; YIndex < YLastIndex; ++YIndex)
		{
			Tile = {XIndex, YIndex};
		}
	}
}

int32 UInventoryComponent::TileToIndex(const FTile Tile) const
{
	const int32 NewIndex = Tile.X + Tile.Y * Columns;
	return NewIndex;
}

FTile UInventoryComponent::IndexToTile(const int32 Index) const
{
	const FTile NewTile = {Index % Columns, Index / Columns};
	return NewTile;
	
}

void UInventoryComponent::EquipItem(UItemObject* Weapon) const
{
	OnEquip.Broadcast(Weapon);
}

void UInventoryComponent::UnEquip() const
{
	OnUnEquip.Broadcast();
}

TMap<UItemObject*, FTile> UInventoryComponent::GetAllItems()
{
	TMap<UItemObject*, FTile> AllItems;
	for(int32 Index = 0; Index != Items.Num(); ++Index)
	{
		auto* CurrentItemObject = Items[Index];
		if(IsValid(CurrentItemObject))
		{
			if(!AllItems.Contains(CurrentItemObject))
			{
				AllItems.Add(CurrentItemObject, IndexToTile(Index));
			}
		}
	}

	return AllItems;
}

void UInventoryComponent::AddItem(UItemObject* ItemObject)
{
	OnAddItem(ItemObject);
}

void UInventoryComponent::RemoveItem(UItemObject* ItemObject)
{
	if(!IsValid(ItemObject)) return;

	for (int32 Index = 0; Index != Items.Num(); ++Index)
	{
		RemoveItemAtIndex(Index, ItemObject);
	}
}

bool UInventoryComponent::IsTileValid(const FTile Tile) const
{
	const bool bResult = Tile.X >= 0 && Tile.Y >= 0 && Tile.X < Columns && Tile.Y < Rows;
	return bResult;
}

void UInventoryComponent::CallInventoryChangedBP() const
{
	if(!OnInventoryChanged.IsBound()) return;
	OnInventoryChanged.Broadcast();
}

void UInventoryComponent::GetItemAtIndex(int32 Index, UItemObject*& ItemOut, bool& bValidOut)
{
	if (Items.IsValidIndex(Index) == false)
	{
		ItemOut = nullptr;
		bValidOut = false;
	}
	else
	{
		ItemOut = Items[Index];
		bValidOut = true;
	}
	
}

void UInventoryComponent::RemoveItemAtIndex(const int32 Index, UItemObject* Item)
{
	if(Items[Index] == Item)
	{
		Items[Index] = nullptr;
		CallInventoryChangedBP();
	}
}
