// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/PlayerCharacter.h"

#include "CharacterAnimInterface.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SpotLightComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Items/InventoryComponent.h"
#include "Items/Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/LogMacros.h"
#include "Components/InteractionComponent.h"
#include "Controllers/Player/MyPlayerController.h"
#include "Components/VaultingComponent.h"
#include "Components/WeaponCombatComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayer, All, All);

APlayerCharacter::APlayerCharacter():
	CrouchEyeOffset(0.0f),
	CrouchSpeed(12.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->bUsePawnControlRotation = false;

	GetMesh()->SetupAttachment(CameraComponent);

	Flashlight = CreateDefaultSubobject<USpotLightComponent>("Flashligth");
	Flashlight->SetupAttachment(CameraComponent);
	FlashlightCone = CreateDefaultSubobject<UStaticMeshComponent>("FlashligthCone");
	FlashlightCone->SetupAttachment(Flashlight);

	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	
	DefaultGrabObjectLocation = CreateDefaultSubobject<UArrowComponent>("DefaultLocationObject");
	DefaultGrabObjectLocation->SetupAttachment(CameraComponent);

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>("Handle");
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	VaultingComponent = CreateDefaultSubobject<UVaultingComponent>("VaultingComponent");

	CombatComponent = CreateDefaultSubobject<UWeaponCombatComponent>("CombatComponent");
	
}

UCombatComponent* APlayerCharacter::GetCombatComponent_Implementation()
{
	return CombatComponent.Get();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(Inventory);
	
	InteractionComponent->Init(PhysicsHandle, DefaultGrabObjectLocation, CameraComponent);
	
	InteractionComponent->OnFlashlightPickUp.AddDynamic(this, &APlayerCharacter::EnableFlashlight);
	InteractionComponent->OnNoteLogPickUp.AddDynamic(this, &APlayerCharacter::OnNotePickup);

	Cast<AMyPlayerController>(GetController())->InitInventory(Inventory);
	Inventory->OnEquip.AddDynamic(this, &APlayerCharacter::EquipWeapon);
	Inventory->OnUnEquip.AddDynamic(this, &APlayerCharacter::UnequipWeapon);

	
	
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const float CrouchInterpTime = FMath::Min(1.0f, CrouchSpeed * DeltaSeconds);
	CrouchEyeOffset = (1.0f - CrouchInterpTime) * CrouchEyeOffset;
	CameraShake();
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
	
}

void APlayerCharacter::CameraShake() const
{
	if(GetVelocity().Length() <= 0)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShakeIdle);
	}
	if (GetVelocity().Length() >= GetMovementComponent()->GetMaxSpeed())
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShakeWalk);
	}
}

void APlayerCharacter::Jumping()
{
	if(GetMovementComponent()->IsCrouching())
	{
		UnCrouch();
		return;
	}

	if(	VaultingComponent->CanVault())
	{
		VaultingComponent->Vault();
	}
	else
	{
		Jump();
	}
	
}

void APlayerCharacter::Interact() 
{
	InteractionComponent->Interact();
}

void APlayerCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if(HalfHeightAdjust == 0) return;

	const float StartBaseEyeHeight = ScaledHalfHeightAdjust;
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CrouchEyeOffset.Z += StartBaseEyeHeight - BaseEyeHeight + HalfHeightAdjust;
	CameraComponent->SetRelativeLocation(FVector{0.0f, 0.0f, BaseEyeHeight}, false);
}

void APlayerCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if(HalfHeightAdjust == 0) return;

	const float StartBaseEyeHeight = ScaledHalfHeightAdjust;
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CrouchEyeOffset.Z += StartBaseEyeHeight - BaseEyeHeight - HalfHeightAdjust;
	CameraComponent->SetRelativeLocation(FVector{0.0f, 0.0f, BaseEyeHeight}, false);
}

void APlayerCharacter::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	CameraComponent->GetCameraView(DeltaTime, OutResult);
	OutResult.Location += CrouchEyeOffset;
	
}

void APlayerCharacter::StartCrouch()
{
	if(bIsCrouched == false)
	{
		Crouch();
	}
	else if(bIsCrouched == true)
	{
		UnCrouch();
	}
}

void APlayerCharacter::SwitchFlashlight()
{
	if(bEnableFlashlight == false) return;

	bFlashlightOn ==  false ? FlashlightActive(true, 100000.0f) : FlashlightActive(false, 0.0f);

}

void APlayerCharacter::FlashlightActive(bool bActive, float Intensity)
{
	Flashlight->SetIntensity(Intensity);
	Flashlight->SetVisibility(bActive);
	UGameplayStatics::PlaySound2D(GetWorld(), FlashlightSound);
	bFlashlightOn = bActive;
}

void APlayerCharacter::OnNotePickup(FNoteData NoteData)
{
	const auto* PlayerController {Cast<AMyPlayerController>(GetController())};
	PlayerController->OnPickupNote.Broadcast(NoteData);
}

void APlayerCharacter::EnableFlashlight()
{
	bEnableFlashlight = true;
}

void APlayerCharacter::EquipWeapon(AWeapon* Weapon)
{
	const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("WeaponSocket"));
	if (!HandSocket) return;
	
	HandSocket->AttachActor(Weapon, GetMesh());
	Weapon->FinishSpawning(GetTransform());
	ICharacterAnimInterface::Execute_EquipWeapon(GetMesh()->GetAnimInstance(), EWeaponType::Knife);
	
}

void APlayerCharacter::UnequipWeapon()
{
	ICharacterAnimInterface::Execute_EquipWeapon(GetMesh()->GetAnimInstance(), EWeaponType::None);
}