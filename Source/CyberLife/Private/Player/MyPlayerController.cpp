// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameSaver.h"
#include "InputAction.h"
#include "Blueprint/UserWidget.h"
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
	/*if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}

	ActiveInventoryWidget = Cast<UInventoryWidget>(CreateWidget(GetWorld(), InventoryWidgetClass));
	ActiveInventoryWidget->Init(PlayerCharacter->GetInteractionComponent()->GetInventory(), 50.0f);
*/

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

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Triggered, this, &AMyPlayerController::ToggleInventoryWidget);
		EnhancedInputComponent->BindAction(SaveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::SaveGame);
		EnhancedInputComponent->BindAction(LoadAction, ETriggerEvent::Triggered, this, &AMyPlayerController::LoadGame);
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
