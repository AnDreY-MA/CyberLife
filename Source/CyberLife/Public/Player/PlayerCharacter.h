// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class AWeapon;
class UInventoryComponent;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class UPhysicsHandleComponent;
class UInteractionComponent;
class UInventoryWidget;

//For PlayerAnimInstance
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnEquipWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipMeeleWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, ValueChanged);

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

	UInteractionComponent* GetInteractionComponent() const { return InteractionComponent; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta=(AllowPrivateAccess))
	UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta=(AllowPrivateAccess))
	USkeletalMeshComponent* MeshArms;

	UPROPERTY(EditDefaultsOnly, Category="Camera")
	TSubclassOf<UCameraShakeBase> CameraShakeIdle;
	UPROPERTY(EditDefaultsOnly, Category="Camera")
	TSubclassOf<UCameraShakeBase> CameraShakeWalk;

	//Input
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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	UInteractionComponent* InteractionComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	UArrowComponent* DefaultGrabObjectLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	UPrimitiveComponent* HoldingObject;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	UPhysicsHandleComponent* PhysicsHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InventoryUI", meta=(AllowPrivateAccess))
	TSubclassOf<UUserWidget> InventoryWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InventoryUI", meta=(AllowPrivateAccess))
	UInventoryWidget* ActiveInventoryWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crouch", meta=(AllowPrivateAccess))
	FVector CrouchEyeOffset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crouch", meta=(AllowPrivateAccess))
	float CrouchSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta=(AllowPrivateAccess))
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta=(AllowPrivateAccess))
	float CurrentHealth;

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
	void ToggleInventoryWidget();

	UFUNCTION()
	void EquipWeapon(AWeapon* Weapon);

	UFUNCTION()
	void UnEquipWeapon();

	void Attack();

	virtual void ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser) override;

	void HideInventoryWidget(APlayerController* PlayerController);
	void ShowInventoryWidget(APlayerController* PlayerController);

	friend class AMyPlayerController;
	
};