// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHUD.h"
#include "UI/StatsWidget.h"
#include "Blueprint/UserWidget.h"
#include "Characters/Player/PlayerCharacter.h"
#include "Controllers/Player/MyPlayerController.h"
#include "Narrative/LogBook.h"
#include "UI/DisplayWidget.h"
#include "UI/NoteWidget.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	auto* PlayerController{Cast<AMyPlayerController>(GetOwningPlayerController())};
	PlayerController->OnPickupNote.AddDynamic(this, &AMainHUD::OnAddedNote);

	if(StatsWidgetClass)
	{
		StatsWidget = CreateWidget<UStatsWidget>(GetOwningPlayerController(), StatsWidgetClass);
		StatsWidget->AddToViewport(-1);
	}

	if(DisplayWidgetClass)
	{
		auto* Character{Cast<APlayerCharacter>(PlayerController->GetCharacter())};
		DisplayWidget = CreateWidget<UDisplayWidget>(GetOwningPlayerController(), DisplayWidgetClass);
		auto* LogBook = PlayerController->FindComponentByClass<ULogBook>();
		DisplayWidget->Init(Character->GetInventoryComponent_Implementation(), 50.0);
	}

	if(PointScreenWidgetClass)
	{
		auto* PointWidget{CreateWidget(PlayerController, PointScreenWidgetClass)};
		PointWidget->AddToViewport();
	}
	
}

void AMainHUD::SwitchDisplay_Implementation()
{
	if(!DisplayWidget) return;

	if(DisplayWidget->IsInViewport())
	{
		HideDisplay();
	}
	else
	{
		ShowDisplay();
	}
}

void AMainHUD::ShowDisplay()
{
	DisplayWidget->AddToViewport();
	DisplayWidget->Show();
	GetOwningPlayerController()->SetShowMouseCursor(true);
	GetOwningPlayerController()->SetInputMode(FInputModeGameAndUI());
}

void AMainHUD::HideDisplay()
{
	DisplayWidget->RemoveFromParent();
	GetOwningPlayerController()->SetShowMouseCursor(false);
	GetOwningPlayerController()->SetInputMode(FInputModeGameOnly());
}

void AMainHUD::OnAddedNote(const FNoteData& InNote)
{
	auto* OwningPlayer{GetOwningPlayerController()};
	OwningPlayer->SetInputMode(FInputModeUIOnly());
	OwningPlayer->SetShowMouseCursor(true);
	OwningPlayer->SetPause(true);
	CreateNoteWidget(InNote);
}

void AMainHUD::ChangeHealth_Implementation(const float Magnitude, const float NewValue, const float OldValue)
{
	StatsWidget->ChangeHealth(NewValue, OldValue, Magnitude);
}

void AMainHUD::ChangeStamina_Implementation(const float Magnitude, const float NewValue, const float OldValue)
{
	StatsWidget->ChangeStamina(NewValue, OldValue, Magnitude);
}


void AMainHUD::OnNoteWidgetClose()
{
	auto* OwningPlayer{GetOwningPlayerController()};
	OwningPlayer->SetInputMode(FInputModeGameOnly());
	OwningPlayer->SetShowMouseCursor(false);
	OwningPlayer->SetPause(false);
}

void AMainHUD::CreateNoteWidget(const FNoteData& InNote)
{
	auto* NoteWidget{CreateWidget<UNoteWidget>(GetOwningPlayerController(), NoteWidgetClass)};
	NoteWidget->Init(InNote);
	NoteWidget->AddToViewport(2);

	NoteWidget->OnClosed.AddDynamic(this, &AMainHUD::OnNoteWidgetClose);
}