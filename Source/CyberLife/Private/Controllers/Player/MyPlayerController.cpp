// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Player/MyPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Abilities/Attributes/CharacterAttributeSet.h"
#include "Abilities/Component/AbilityComponentBase.h"
#include "Blueprint/UserWidget.h"
#include "Characters/Player/PlayerCharacter.h"
#include "GameFramework/HUD.h"
#include "Items/Item.h"
#include "UI/HUD/MainHUDInterface.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayer, All, All);

AMyPlayerController::AMyPlayerController()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponentBase>("AbilityComponent");
	LogBook = CreateDefaultSubobject<ULogBook>("LogBook");
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());

	AbilityComponent->InitAbilityActorInfo(this, GetPawn());

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}

	PlayerCharacter->OnAddNoteData.AddDynamic(this, &AMyPlayerController::AddNote);

	auto* Attribute = AbilityComponent->GetSet<UCharacterAttributeSet>();
	Attribute->OnHealthChanged.AddDynamic(this, &AMyPlayerController::OnChangeHealth);
	Attribute->OnStaminaChanged.AddDynamic(this, &AMyPlayerController::OnChangeStamina);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Look);

		//Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Jumping);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this,
		                                   &AMyPlayerController::StopJumping);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this,
		                                   &AMyPlayerController::Interact);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Crouch);

		EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Triggered, this,
		                                   &AMyPlayerController::ToggleInventoryWidget);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Attack);

		EnhancedInputComponent->BindAction(FlashlightAction, ETriggerEvent::Triggered, this,
		                                   &AMyPlayerController::SwitchFlashlight);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this,
		                                   &AMyPlayerController::SprintStart);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this,
		                                   &AMyPlayerController::SprintEnd);
	}
}


UAbilitySystemComponent* AMyPlayerController::GetAbilitySystemComponent() const
{
	return AbilityComponent;
}

void AMyPlayerController::Jumping()
{
	PlayerCharacter->Jumping();
}

void AMyPlayerController::StopJumping()
{
	PlayerCharacter->StopJumping();
}

void AMyPlayerController::Interact()
{
	PlayerCharacter->Interact();
}

void AMyPlayerController::Crouch()
{
	PlayerCharacter->StartCrouch();
}

void AMyPlayerController::SwitchFlashlight()
{
	AbilityComponent->ActivateAbility(EAbilityInputID::ToggleFlashlight);
}

void AMyPlayerController::Attack()
{
	AbilityComponent->ActivateAbility(EAbilityInputID::Attack);
	
}

void AMyPlayerController::SprintStart()
{
	AbilityComponent->ActivateAbility(EAbilityInputID::Sprint);
}

void AMyPlayerController::SprintEnd()
{
	AbilityComponent->ReleaseAbility(EAbilityInputID::Sprint);
}

void AMyPlayerController::InitInventory(UInventoryComponent* InventoryComponent)
{
	//DisplayWidget = Cast<UDisplayWidget>(CreateWidget(this, DisplayWidgetClass));
	//DisplayWidget->Init(InventoryComponent, 50.f, LogBook);

}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
	PlayerCharacter->Move(Value);

}

void AMyPlayerController::Look(const FInputActionValue& Value)
{
	PlayerCharacter->Look(Value);

}

void AMyPlayerController::ToggleInventoryWidget()
{
	IMainHUDInterface::Execute_SwitchDisplay(GetHUD());
	
}

void AMyPlayerController::AddNote(FNoteData NoteData)
{
	UE_LOG(LogTemp, Warning, TEXT("ADDED Note"));
	LogBook->AddNote(NoteData);

}

void AMyPlayerController::OnChangeHealth(const float NewValue, const float OldValue, const float Magnitude)
{
	if(auto* HUD{GetHUD()}; HUD->Implements<UMainHUDInterface>())
	{
		IMainHUDInterface::Execute_ChangeHealth(HUD, Magnitude, NewValue, OldValue);
	}
	if(NewValue <= 0.0f)
	{
		GetPawn()->Destroy();
	}
}

void AMyPlayerController::OnChangeStamina(const float NewValue, const float OldValue, const float Magnitude)
{
	if(auto* HUD{GetHUD()}; HUD->Implements<UMainHUDInterface>())
	{
		IMainHUDInterface::Execute_ChangeStamina(HUD, Magnitude, NewValue, OldValue);
	}
}
