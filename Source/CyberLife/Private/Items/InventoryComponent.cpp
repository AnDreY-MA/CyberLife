#include "Items/InventoryComponent.h"

#include "Items/Item.h"
#include "Items/Data/ItemData.h"
#include "Items/Weapon.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/GridElements.h"

UInventoryComponent::UInventoryComponent() :
    Columns(0),
    Rows(0)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ItemDatas.SetNum(Columns * Rows);
}

bool UInventoryComponent::IsSpaceAvailable(UItemData* ItemObject, int32 TopLeftIndex)
{
	const int32 XFirstIndex = IndexToTile(TopLeftIndex).X;
	const int32 XLastIndex = IndexToTile(TopLeftIndex).X + (ItemObject->GetDimensions().X - 1);
	const int32 YFirstIndex = IndexToTile(TopLeftIndex).Y;
	const int32 YLastIndex = IndexToTile(TopLeftIndex).Y + (ItemObject->GetDimensions().Y - 1);
	for (int32 X = XFirstIndex; X <= XLastIndex; ++X)
	{
		for(int32 Y = YFirstIndex; Y <= YLastIndex; ++Y)
		{
			FTile Tile {X, Y};
			if(IsTileValid(Tile) == false) return false;

			UItemData* ItemOut;
			bool bValidOut;
			GetItemAtIndex(TileToIndex(Tile), ItemOut, bValidOut);
			if(bValidOut == false) return false;
			if(IsValid(ItemOut)) return false;
		}
	}
	
	return true;
}

void UInventoryComponent::ForEachIndex(UItemData* ItemObject, int32 TopLeftIndex, FTile& Tile)
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

int32 UInventoryComponent::TileToIndex(const FTile& Tile) const
{
	const int32 NewIndex = Tile.X + Tile.Y * Columns;
	return NewIndex;
}

FTile UInventoryComponent::IndexToTile(const int32 Index) const
{
	const FTile NewTile = {Index % Columns, Index / Columns};
	return NewTile;
	
}

TMap<UItemData*, FTile> UInventoryComponent::GetAllItems()
{
	TMap<UItemData*, FTile> AllItems;
	for(int32 Index = 0; Index != ItemDatas.Num(); ++Index)
	{
		TObjectPtr<UItemData> CurrentItemObject = ItemDatas[Index];
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

bool UInventoryComponent::TryAddItem(UItemData* ItemObject)
{
	int32 Index = 0;
	for ([[maybe_unused]] UItemData* Item : ItemDatas)
	{
		if(IsSpaceAvailable(ItemObject, Index))
		{
			AddItemAt(ItemObject, Index);
			return true;
		}
		++Index;
	}
	
	return false;
}

void UInventoryComponent::RemoveItem(UItemData* ItemObject)
{
	if(!IsValid(ItemObject)) return;

	for (int32 Index = 0; Index != ItemDatas.Num(); ++Index)
	{
		RemoveItemAtIndex(Index, ItemObject);
	}
}

void UInventoryComponent::EquipWeapon(UItemData* ItemObject)
{
	if(!ItemObject->GetItemClass()->ImplementsInterface(UWeaponInterface::StaticClass()))
	{
		return;
	}

	auto* Weapon = GetWorld()->SpawnActorDeferred<AWeapon>(ItemObject->GetItemClass(), GetOwner()->GetTransform(), GetOwner(), GetOwner()->GetInstigator());
	Weapon->SetItemObject(ItemObject);
	EquipedWeapon = Weapon;
	EquipedWeapon->Equip();
	
	OnEquip.Broadcast(EquipedWeapon);
	
}

void UInventoryComponent::UnequipWeapon()
{
	EquipedWeapon->UnEquip();
	OnUnEquip.Broadcast();
	
}

void UInventoryComponent::SpawnItem(UItemData* InItem, const bool bGroundClamp)
{
	const float SpawnDistance{200.f};
	FVector SpawnLocation(GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * SpawnDistance);
	if(bGroundClamp)
	{
		FHitResult HitResult;
		if(UKismetSystemLibrary::LineTraceSingle(GetWorld(), SpawnLocation, SpawnLocation-FVector(0.0, 0.0, 1000.0),
			TraceTypeQuery1, true, {GetOwner()}, EDrawDebugTrace::None, HitResult, true))
		{
			SpawnLocation = HitResult.Location;
		}
	}
	FTransform Transform;
	Transform.SetLocation(SpawnLocation);
	Transform.SetScale3D({1.0, 1.0, 1.0});
	auto* SpawnedItem = GetWorld()->SpawnActorDeferred<AItem>(InItem->GetItemClass(), Transform);
	SpawnedItem->SetItemObject(InItem);
	SpawnedItem->FinishSpawning(Transform);
}

bool UInventoryComponent::IsTileValid(const FTile& Tile) const
{
	const bool bResult = Tile.X >= 0 && Tile.Y >= 0 && Tile.X < Columns && Tile.Y < Rows;
	return bResult;
}

void UInventoryComponent::AddItemAt(UItemData* ItemObject, const int32 TopLeftIndex)
{
	const int32 XFirstIndex = IndexToTile(TopLeftIndex).X;
	const int32 XLastIndex = IndexToTile(TopLeftIndex).X + (ItemObject->GetDimensions().X - 1);
	const int32 YFirstIndex = IndexToTile(TopLeftIndex).Y;
	const int32 YLastIndex = IndexToTile(TopLeftIndex).Y + (ItemObject->GetDimensions().Y - 1);

	for (int32 X = XFirstIndex; X <= XLastIndex; ++X)
	{
		for(int32 Y = YFirstIndex; Y <= YLastIndex; ++Y)
		{
			const FTile Tile {X, Y};
			ItemDatas[TileToIndex(Tile)] = ItemObject;
		}
	}

	CallInventoryChangedBP();
}

void UInventoryComponent::CallInventoryChangedBP() const
{
	if(!OnInventoryChanged.IsBound()) return;
	
	OnInventoryChanged.Broadcast();
}

void UInventoryComponent::GetItemAtIndex(const int32 Index, UItemData*& ItemOut, bool& bValidOut)
{
	if (ItemDatas.IsValidIndex(Index) == false)
	{
		ItemOut = nullptr;
		bValidOut = false;
	}
	else
	{
		ItemOut = ItemDatas[Index];
		bValidOut = true;
	}
	
}

void UInventoryComponent::RemoveItemAtIndex(const int32 Index, const UItemData* Item)
{
	if(ItemDatas[Index] == Item)
	{
		ItemDatas[Index] = nullptr;
		CallInventoryChangedBP();
	}
	
}