// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Narrative/NoteData.h"
#include "MyPlayerController.generated.h"

class AMainHUD;
class ULogBook;
class AItem;
class UInventoryComponent;
class UGameSaver;
class APlayerCharacter;
class UInputMappingContext;
class UInputAction;
class UStatsWidget;
class UDisplayWidget;
class AWeapon;

UCLASS()
class CYBERLIFE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();
	
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
#pragma endregion Input
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InventoryUI", meta=(AllowPrivateAccess))
	TSubclassOf<UUserWidget> DisplayWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InventoryUI", meta=(AllowPrivateAccess))
	TObjectPtr<UDisplayWidget> DisplayWidget;

	UPROPERTY(EditDefaultsOnly, Category="HUD")
	TObjectPtr<AMainHUD> MainHUD;

	UPROPERTY()
	TObjectPtr<UInventoryComponent> Inventory;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ULogBook> LogBook;

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
	void AddNote(FNoteData NoteData);

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
