// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SpotLightComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Items/MeeleWeapon.h"
#include "Items/Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/LogMacros.h"
#include "Player/InteractionComponent.h"
#include "Player/MyPlayerController.h"
#include "Player/VaultingComponent.h"

DEFINE_LOG_CATEGORY_STATIC(PlayerLog, All, All);

// Sets default values
APlayerCharacter::APlayerCharacter():
	CrouchEyeOffset(0.0f),
	CrouchSpeed(12.0f),
	MaxHealth(100.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->bUsePawnControlRotation = false; 

	MeshArms = CreateDefaultSubobject<USkeletalMeshComponent>("Arms");
	MeshArms->SetupAttachment(CameraComponent);

	Flashlight = CreateDefaultSubobject<USpotLightComponent>("Flashligth");
	Flashlight->SetupAttachment(CameraComponent);
	FlashlightCone = CreateDefaultSubobject<UStaticMeshComponent>("FlashligthCone");
	FlashlightCone->SetupAttachment(Flashlight);

	Sylinder = CreateDefaultSubobject<UStaticMeshComponent>("Interact");
	Sylinder->SetupAttachment(CameraComponent);
	
	
	DefaultGrabObjectLocation = CreateDefaultSubobject<UArrowComponent>("DefaultLocationObject");
	DefaultGrabObjectLocation->SetupAttachment(CameraComponent);

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>("Handle");
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	VaultingComponent = CreateDefaultSubobject<UVaultingComponent>("VaultingComponent");

	CurrentHealth = MaxHealth;
	
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const auto* Contr= Cast<AMyPlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Contr->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}

		InteractionComponent->Init(PhysicsHandle, DefaultGrabObjectLocation, CameraComponent);
	}

	InteractionComponent->OnWeaponEquip.AddDynamic(this, &APlayerCharacter::EquipWeapon);
	InteractionComponent->OnWeaponUnEquip.AddDynamic(this, &APlayerCharacter::UnEquipWeapon);
	InteractionComponent->OnFlashlightPickUp.AddDynamic(this, &APlayerCharacter::EnableFlashlight);
	InteractionComponent->OnNoteLogPickUp.AddDynamic(this, &APlayerCharacter::AddNote);
	
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const float CrouchInterpTime = FMath::Min(1.0f, CrouchSpeed * DeltaSeconds);
	CrouchEyeOffset = (1.0f - CrouchInterpTime) * CrouchEyeOffset;
	CameraShake();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jumping);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Crouch
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &APlayerCharacter::StartCrouch);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
		
		EnhancedInputComponent->BindAction(FlashlightAction, ETriggerEvent::Started, this, &APlayerCharacter::SwitchFlashlight);
		

		//Attack
		//EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Attack);
		
	}

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
	
	if (bFlashlightOn ==  false)
	{
		FlashlightActive(true, 100000.0f);
	}
	else
	{
		FlashlightActive(false, 0.0f);
	}

}

void APlayerCharacter::FlashlightActive(bool bActive, float Intensity)
{
	Flashlight->SetIntensity(Intensity);
	Flashlight->SetVisibility(bActive);
	UGameplayStatics::PlaySound2D(GetWorld(), FlashlightSound);
	bFlashlightOn = bActive;
}

void APlayerCharacter::AddNote(FNoteData NoteData)
{
	OnAddNoteData.Broadcast(NoteData);
}

void APlayerCharacter::EquipWeapon(AWeapon* Weapon)
{
	const USkeletalMeshSocket* HandSocket = MeshArms->GetSocketByName(FName("WeaponSocket"));
	if (!HandSocket) return;
	
	HandSocket->AttachActor(Weapon, MeshArms);
	OnEquipWeapon.Broadcast();
	if (Cast<AMeeleWeapon>(Weapon)) OnEquipMeeleWeapon.Broadcast();
	
}

void APlayerCharacter::UnEquipWeapon()
{
	OnUnEquipWeapon.Broadcast();
}

void APlayerCharacter::EnableFlashlight()
{
	UE_LOG(LogTemp, Warning, TEXT("Enabled"));
	bEnableFlashlight = true;
}

void APlayerCharacter::Attack(AWeapon* EquipedWeapon)
{
	if (InteractionComponent->IsHoldingObject())
	{
		InteractionComponent->ThrowObject();
	}
	else
	{
		if (!EquipedWeapon) return;

		EquipedWeapon->Attack(this);
		const auto* MeeleWeapon = Cast<AMeeleWeapon>(EquipedWeapon);
		if (MeeleWeapon && MeeleAttackAnim)
		{
			UAnimInstance* AnimInstance = MeshArms->GetAnimInstance();
			check(AnimInstance);
			AnimInstance->Montage_Play(MeeleAttackAnim);
		}
	}
	
}

void APlayerCharacter::ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator,
	AActor* DamageCauser)
{
	Super::ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);

	CurrentHealth -= DamageTaken;

	if(OnHealthChanged.IsBound())
	{
		OnHealthChanged.Broadcast(CurrentHealth);
	}
	
	if (CurrentHealth <= 0.0)
	{
		UE_LOG(PlayerLog, Display, TEXT("Dead"));
	}	
}
