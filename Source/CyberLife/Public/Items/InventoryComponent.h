// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemData;
class AWeapon;
struct FTile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquip, AWeapon*, Weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnEquip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS( ClassGroup=(InventoryComponent), Blueprintable)
class CYBERLIFE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	FOnEquip OnEquip;
	FOnUnEquip OnUnEquip;

	UFUNCTION(BlueprintCallable)
	bool IsSpaceAvailable(UItemData* ItemObject, int32 TopLeftIndex);

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetColumns() const { return Columns; }
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetRows() const { return Rows; }
	
	UFUNCTION(BlueprintPure)
	int32 TileToIndex(const FTile& Tile) const;
	UFUNCTION(BlueprintPure)
	FTile IndexToTile(int32 Index) const;

	UFUNCTION(BlueprintCallable)
	TMap<UItemData*, FTile> GetAllItems();

	UFUNCTION(BlueprintCallable)
	bool TryAddItem(UItemData* ItemObject);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(UItemData* ItemObject);
	
	UPROPERTY(BlueprintAssignable)
	FOnInventoryChanged OnInventoryChanged;

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(UItemData* ItemObject);
	UFUNCTION(BlueprintCallable)
	void UnequipWeapon();

	UFUNCTION(BlueprintCallable)
	void SpawnItem(UItemData* InItem, const bool bGroundClamp);

	TObjectPtr<AWeapon> GetWeapon() const { return EquipedWeapon; }

	UFUNCTION(BlueprintCallable)
	void AddItemAt(UItemData* ItemObject, int32 TopLeftIndex);

protected:
	UFUNCTION(BlueprintCallable)
	bool IsTileValid(const FTile& Tile) const;

	UFUNCTION(BlueprintCallable)
	void CallInventoryChangedBP() const;

	UFUNCTION(BlueprintCallable, meta=(BlueprintProtected))
	void GetItemAtIndex(int32 Index, UItemData*& ItemOut, bool& bValidOut);

	void RemoveItemAtIndex(const int32 Index, const UItemData* Item);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	int32 Columns;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	int32 Rows;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TArray<TObjectPtr<UItemData>> ItemDatas;
	
	UPROPERTY()
	TObjectPtr<AWeapon> EquipedWeapon;
	
	virtual void BeginPlay() override;

	void ForEachIndex(UItemData* ItemObject, int32 TopLeftIndex, FTile& Tile);
	
};