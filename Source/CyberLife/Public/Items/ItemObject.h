// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.generated.h"

class AItem;

UCLASS(BlueprintType, Blueprintable)
class CYBERLIFE_API UItemObject : public UObject
{
	GENERATED_BODY()
public:
	UItemObject();

private:
	UPROPERTY()
	TSubclassOf<AItem> ItemClass;
	UPROPERTY()
	FString BPItemName;
	UPROPERTY()
	FIntPoint Dimensions;

	UPROPERTY()
	UStaticMesh* Mesh;
	UPROPERTY()
	UMaterialInterface* IconRotated;
	UPROPERTY()
	UMaterialInterface* Icon;

	UPROPERTY()
	bool bIsRotated;
	UPROPERTY()
	bool bEquiped { false};

	friend class AItem;

public:
	UFUNCTION(BlueprintCallable)
	FIntPoint GetDimensions() const;
	UFUNCTION(BlueprintCallable)
	UMaterialInterface* GetIcon() const;
	UFUNCTION(BlueprintCallable)
	void Rotate();
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsRotated() const { return bIsRotated; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TSubclassOf<AItem> GetItemClass() const { return ItemClass; }

	FORCEINLINE FString GetBPItemName() const { return BPItemName; }

	void EquipWeapon();
	void UnEquipWeapon();

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsEquiped() const { return bEquiped; }

};
