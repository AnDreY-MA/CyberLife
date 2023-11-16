// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameSaver.h"
#include "InputAction.h"
#include "Blueprint/UserWidget.h"
#include "Items/InventoryComponent.h"
#include "Items/Item.h"
#include "Items/ItemObject.h"
#include "Items/Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Player/InteractionComponent.h"
#include "Player/PlayerCharacter.h"
#include "UI/InventoryWidget.h"
#include "UI/StatsWidget.h"



void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());

	CreateWidget(this, PointScreen)->AddToViewport();
	StatsWidget = Cast<UStatsWidget>(CreateWidget(this, Stats));
	check(StatsWidget);
	StatsWidget->AddToViewport();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}
	

	if(UGameplayStatics::DoesSaveGameExist("save1", 0))
	{
		GameSaver = Cast<UGameSaver>(UGameplayStatics::LoadGameFromSlot("save1", 0));
	}

	else
	{
		GameSaver = Cast<UGameSaver>(UGameplayStatics::CreateSaveGameObject(UGameSaver::StaticClass()));
		check(GameSaver);
		UGameplayStatics::SaveGameToSlot(GameSaver, "save1", 0);
	}
	
}

void AMyPlayerController::InitInventory(UInventoryComponent* InventoryComponent)
{
	Inventory = InventoryComponent;

	ActiveInventoryWidget = Cast<UInventoryWidget>(CreateWidget(GetWorld(), InventoryWidgetClass));
	ActiveInventoryWidget->Init(Inventory, 50.0f);

	Inventory->OnEquip.AddDynamic(this, &AMyPlayerController::EquipWeapon);
	Inventory->OnUnEquip.AddDynamic(this, &AMyPlayerController::UnEquipWeapon);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Triggered, this, &AMyPlayerController::ToggleInventoryWidget);
		EnhancedInputComponent->BindAction(SaveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::SaveGame);
		EnhancedInputComponent->BindAction(LoadAction, ETriggerEvent::Triggered, this, &AMyPlayerController::LoadGame);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AMyPlayerController::AttackWeapon);
	}
}

void AMyPlayerController::ToggleInventoryWidget()
{
	if(ActiveInventoryWidget->IsInViewport())
	{
		HideInventoryWidget();
	}
	else
	{
		ShowInventoryWidget();
	}
}

void AMyPlayerController::HideInventoryWidget()
{
	ActiveInventoryWidget->RemoveFromParent();
	SetShowMouseCursor(false);
	const FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
}

void AMyPlayerController::ShowInventoryWidget()
{
	ActiveInventoryWidget->AddToViewport();
	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeGameAndUI);
	SetShowMouseCursor(true);
}

void AMyPlayerController::EquipWeapon(UItemObject* WeaponItemObject)
{
	auto* Weapon = CreateBlueprintDefferd<AWeapon>(GetWorld(), WeaponItemObject->GetBPItemName(), PlayerCharacter->GetActorTransform());
	Weapon->SetItemObject(WeaponItemObject);
	EquipedWeapon = Weapon;
	EquipedWeapon->Equip();
	PlayerCharacter->EquipWeapon(EquipedWeapon);
}

void AMyPlayerController::UnEquipWeapon()
{
	EquipedWeapon->UnEquip();
	EquipedWeapon->Destroy();
	EquipedWeapon = nullptr;
	PlayerCharacter->UnEquipWeapon();
}

void AMyPlayerController::AttackWeapon()
{
	PlayerCharacter->Attack(EquipedWeapon);
}

void AMyPlayerController::SaveGame()
{
	if(!UGameplayStatics::DoesSaveGameExist("save1", 0)) return;

	check(PlayerCharacter);
	GameSaver->SavePlayer(PlayerCharacter->GetActorTransform());
	UGameplayStatics::SaveGameToSlot(GameSaver, "save1", 0);
}

void AMyPlayerController::LoadGame()
{
	if(!UGameplayStatics::DoesSaveGameExist("save1", 0)) return;

	PlayerCharacter->SetActorTransform(GameSaver->GetPlayerPosition());
	
}