// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Characters/CharacterBase.h"
#include "Components/CombatComponentInterface.h"
#include "Components/InteractionComponentInterface.h"
#include "GameFramework/Character.h"
#include "Items/InventoryComponentInterface.h"
#include "Narrative/NoteData.h"
#include "PlayerCharacter.generated.h"

class UWeaponCombatComponent;
class UVaultingComponent;
class AItem;
class AWeapon;
class UInventoryComponent;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class UPhysicsHandleComponent;
class UInteractionComponent;
class USpotLightComponent;

//For PlayerAnimInstance
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipMeeleWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, ValueChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddNoteData, FNoteData, NoteData);


UCLASS()
class CYBERLIFE_API APlayerCharacter : public ACharacterBase, public IInteractionComponentInterface, public ICombatComponentInterface, public IInventoryComponentInterface
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	
	FOnHealthChanged OnHealthChanged;
	FOnAddNoteData OnAddNoteData;

	FORCEINLINE virtual UInteractionComponent* GetInteractionComponent_Implementation() override { return InteractionComponent; }
	virtual UCombatComponent* GetCombatComponent_Implementation() override;
	
	FORCEINLINE virtual UInventoryComponent* GetInventoryComponent_Implementation() override { return Inventory; }

	FORCEINLINE USkeletalMeshComponent* GetArmMesh() { return GetMesh(); }
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta=(AllowPrivateAccess))
	TObjectPtr<UCameraComponent> CameraComponent;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta=(AllowPrivateAccess))
	//TObjectPtr<UStaticMeshComponent> Sylinder;

	UPROPERTY(EditAnywhere, Category="FlashLight", meta = (AllowPrivateAccess))
	TObjectPtr<USpotLightComponent> Flashlight;
	UPROPERTY(EditAnywhere, Category="FlashLight", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> FlashlightCone;

	UPROPERTY(EditDefaultsOnly, Category="FlashLight")
	TObjectPtr<USoundBase> FlashlightSound;

	UPROPERTY(EditDefaultsOnly, Category="Camera")
	TSubclassOf<UCameraShakeBase> CameraShakeIdle;
	UPROPERTY(EditDefaultsOnly, Category="Camera")
	TSubclassOf<UCameraShakeBase> CameraShakeWalk;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction", meta=(AllowPrivateAccess))
	TObjectPtr<UInteractionComponent> InteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction|Grabing", meta=(AllowPrivateAccess))
	TObjectPtr<UArrowComponent> DefaultGrabObjectLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction|Grabing", meta=(AllowPrivateAccess))
	TObjectPtr<UPrimitiveComponent> HoldingObject;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction|Grabing", meta=(AllowPrivateAccess))
	TObjectPtr<UPhysicsHandleComponent> PhysicsHandle;
	
	UPROPERTY(EditDefaultsOnly, Category="Vaulting")
	TObjectPtr<UVaultingComponent> VaultingComponent;

	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TObjectPtr<UInventoryComponent> Inventory;
	
	UPROPERTY(EditDefaultsOnly, Category="CombatComponent")
	TObjectPtr<UWeaponCombatComponent> CombatComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crouch", meta=(AllowPrivateAccess))
	FVector CrouchEyeOffset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crouch", meta=(AllowPrivateAccess))
	float CrouchSpeed;
	
	UPROPERTY()
	bool bFlashlightOn{ false };

	UPROPERTY()
	bool bEnableFlashlight {false};

	/*
		Metods
	*/
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void CameraShake() const;
	void Jumping();
	void Interact();
	
	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;
	
	void StartCrouch();
	void SwitchFlashlight();
	void FlashlightActive(bool bActive, float Intensity);

	UFUNCTION()
	void AddNote(const FNoteData& NoteData);
	
	UFUNCTION()
	void EquipWeapon(AWeapon* Weapon);
	UFUNCTION()
	void UnequipWeapon();

	UFUNCTION()
	void EnableFlashlight();

	friend class AMyPlayerController;
	
};