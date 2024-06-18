// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Narrative/NoteData.h"
#include "AbilitySystemInterface.h"
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
class UAbilityComponentBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickupNote, const FNoteData&, InNote);

UCLASS()
class CYBERLIFE_API AMyPlayerController : public APlayerController, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMyPlayerController();

	FOnPickupNote OnPickupNote;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	UFUNCTION(BlueprintCallable)
	void InitInventory(UInventoryComponent* InventoryComponent);

private:

	UPROPERTY(EditDefaultsOnly, Category="Ability")
	TObjectPtr<UAbilityComponentBase> AbilityComponent;
	
	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerCharacter;


#pragma region Input
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> MappingContext;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> CrouchAction;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> FlashlightAction;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> ToggleInventoryAction;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> AttackAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> SprintAction;

#pragma endregion Input
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> DisplayWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta=(AllowPrivateAccess))
	TObjectPtr<UDisplayWidget> DisplayWidget;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> PointScreen;

	UPROPERTY(BlueprintReadWrite,Category="Widgets",  meta=(AllowPrivateAccess))
	TObjectPtr<UStatsWidget> StatsWidget;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ULogBook> LogBook;

	/**
	 * Methods
	 */

	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent()override;

	void SprintStart();
	void SprintEnd();
	void Jumping();
	void StopJumping();
	void Interact();
	void Crouch();
	void SwitchFlashlight();
	
	void Attack();
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void ToggleInventoryWidget();
	void HideInventoryWidget();
	void ShowInventoryWidget();

	UFUNCTION()
	void AddNote(FNoteData NoteData);

	UFUNCTION()
	void OnChangeHealth(const float NewValue, const float OldValue, const float Magnitude);
	UFUNCTION()
	void OnChangeStamina(const float NewValue, const float OldValue, const float Magnitude);

	friend class APlayerCharacter;
	
};