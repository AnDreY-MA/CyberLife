// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class AItem;
class UInventoryComponent;
class UGameSaver;
class APlayerCharacter;
class UInputMappingContext;
class UInputAction;
class UStatsWidget;
class UInventoryWidget;
class AWeapon;

UCLASS()
class CYBERLIFE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AWeapon* GetWaepon() const { return EquipedWeapon; }

	UInventoryComponent* GetInventory() { return Inventory; }

protected:
	UFUNCTION(BlueprintCallable)
	void InitInventory(UInventoryComponent* InventoryComponent);

private:
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PointScreen;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> Stats;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UStatsWidget* StatsWidget;

#pragma region Input
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> MappingContext;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> ToggleInventoryAction;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> AttackAction;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> SaveAction;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> LoadAction;
#pragma endregion  Input
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InventoryUI", meta=(AllowPrivateAccess))
	TSubclassOf<UUserWidget> InventoryWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InventoryUI", meta=(AllowPrivateAccess))
	TObjectPtr<UInventoryWidget> ActiveInventoryWidget;

	UPROPERTY()
	TObjectPtr<UInventoryComponent> Inventory;

	UPROPERTY()
	TObjectPtr<AWeapon> EquipedWeapon;

	UPROPERTY()
	TObjectPtr<UGameSaver> GameSaver;

	/**
	 * Methods
	 */
	
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void ToggleInventoryWidget();
	void HideInventoryWidget();
	void ShowInventoryWidget();

	UFUNCTION()
	void EquipWeapon(UItemObject* WeaponItemObject);
	UFUNCTION()
	void UnEquipWeapon();
	void AttackWeapon();
	
	void SaveGame();
	void LoadGame();

	template<typename T>
	T* CreateBlueprintDefferd(UWorld* World, const FString& Name, const FTransform& Transform = FTransform::Identity)
	{
		const UBlueprint* Blueprint = LoadObject<UBlueprint>(nullptr, *Name);
		return (World && Blueprint) ? World->SpawnActorDeferred<T>(Blueprint->GeneratedClass, Transform) : nullptr;
	}

	friend class APlayerCharacter;
};
