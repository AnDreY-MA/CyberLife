// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AWeapon;
struct FTile;
class UItemObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquip, UItemObject*, WeaponItemObject);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnEquip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS( ClassGroup=(Custom), Blueprintable)
class CYBERLIFE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	FOnEquip OnEquip;
	FOnUnEquip OnUnEquip;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	int32 Columns;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	int32 Rows;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TArray<UItemObject*> Items;

	UPROPERTY()
	bool bEquiped;

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetColumns() const { return Columns; }
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetRows() const { return Rows; }
	UFUNCTION(BlueprintPure)
	int32 TileToIndex(FTile Tile) const;
	UFUNCTION(BlueprintPure)
	FTile IndexToTile(int32 Index) const;

	UFUNCTION(BlueprintCallable)
	void EquipItem(UItemObject* Weapon) const;
	UFUNCTION(BlueprintCallable)
	void UnEquip() const;

	UFUNCTION(BlueprintCallable)
	TMap<UItemObject*, FTile> GetAllItems();

	void AddItem(UItemObject* ItemObject);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(UItemObject* ItemObject);
	
	UPROPERTY(BlueprintAssignable)
	FOnInventoryChanged OnInventoryChanged;

private:
	virtual void BeginPlay() override;

	void ForEachIndex(UItemObject* ItemObject, int32 TopLeftIndex, FTile& Tile);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnAddItem(UItemObject* Item);
	UFUNCTION(BlueprintCallable)
	bool IsTileValid(const FTile Tile) const;

	UFUNCTION(BlueprintCallable)
	void CallInventoryChangedBP() const;

	UFUNCTION(BlueprintCallable, meta=(BlueprintProtected))
	void GetItemAtIndex(int32 Index, UItemObject*& ItemOut, bool& bValidOut);

	void RemoveItemAtIndex(const int32 Index, UItemObject* Item);
	
};
