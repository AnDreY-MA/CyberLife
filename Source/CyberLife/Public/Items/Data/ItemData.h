// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

class AItem;
/**
 * 
 */
UCLASS()
class CYBERLIFE_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category="Base")
	TSubclassOf<AItem> ItemClass;
	UPROPERTY(EditDefaultsOnly, Category="Base")
	FString BPItemName;
	UPROPERTY(EditDefaultsOnly, Category="Base")
	FPrimaryAssetType ItemType;
	
	UPROPERTY(EditDefaultsOnly, Category="Base")
	UStaticMesh* Mesh;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	FIntPoint Dimensions;
	UPROPERTY(EditDefaultsOnly, Category="UI")
	UMaterialInterface* IconRotated;
	UPROPERTY(EditDefaultsOnly, Category="UI")
	UMaterialInterface* Icon;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	bool bIsRotated;
	
	UPROPERTY(EditDefaultsOnly, Category="Base")
	bool bEquiped { false };

	friend class AItem;
	friend class UInventoryComponent;

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

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	
};