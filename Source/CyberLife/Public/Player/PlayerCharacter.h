// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "Narrative/NoteData.h"
#include "PlayerCharacter.generated.h"

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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnEquipWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipMeeleWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, ValueChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddNoteData, FNoteData, NoteData);


UCLASS()
class CYBERLIFE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	UPROPERTY(BlueprintAssignable)
	FOnEquipWeapon OnEquipWeapon;
	UPROPERTY(BlueprintAssignable)
	FOnUnEquipWeapon OnUnEquipWeapon;
	UPROPERTY(BlueprintAssignable)
	FOnEquipMeeleWeapon OnEquipMeeleWeapon;
	
	FOnHealthChanged OnHealthChanged;
	FOnAddNoteData OnAddNoteData;

	UInteractionComponent* GetInteractionComponent() const { return InteractionComponent; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta=(AllowPrivateAccess))
	UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta=(AllowPrivateAccess))
	USkeletalMeshComponent* MeshArms;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta=(AllowPrivateAccess))
	UStaticMeshComponent* Sylinder;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	USpotLightComponent* Flashlight;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	UStaticMeshComponent* FlashlightCone;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* FlashlightSound;

	UPROPERTY(EditDefaultsOnly, Category="Camera")
	TSubclassOf<UCameraShakeBase> CameraShakeIdle;
	UPROPERTY(EditDefaultsOnly, Category="Camera")
	TSubclassOf<UCameraShakeBase> CameraShakeWalk;

#pragma region Input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess))
	UInputMappingContext* MappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess))
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess))
	UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess))
	UInputAction* JumpAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess))
	UInputAction* InteractAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess))
	UInputAction* CrouchAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess))
	UInputAction* ToggleInventoryAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess))
	UInputAction* AttackAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess))
	UInputAction* FlashlightAction;
#pragma endregion Input
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	TObjectPtr<UInteractionComponent> InteractionComponent;

	UPROPERTY(EditDefaultsOnly, Category="Vaulting")
	TObjectPtr<UVaultingComponent> VaultingComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	TObjectPtr<UArrowComponent> DefaultGrabObjectLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	TObjectPtr<UPrimitiveComponent> HoldingObject;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	TObjectPtr<UPhysicsHandleComponent> PhysicsHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crouch", meta=(AllowPrivateAccess))
	FVector CrouchEyeOffset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crouch", meta=(AllowPrivateAccess))
	float CrouchSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta=(AllowPrivateAccess))
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta=(AllowPrivateAccess))
	float CurrentHealth;

	UPROPERTY()
	bool bFlashlightOn{ false };

	UPROPERTY()
	bool bEnableFlashlight {false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation", meta=(AllowPrivateAccess))
	UAnimMontage* MeeleAttackAnim;
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
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
	void AddNote(FNoteData NoteData);

	UFUNCTION()
	void EquipWeapon(AWeapon* Weapon);

	UFUNCTION()
	void UnEquipWeapon();

	UFUNCTION()
	void EnableFlashlight();

	void Attack(AWeapon* EquipedWeapon);

	virtual void ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser) override;

	friend class AMyPlayerController;
	
};