// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD/MainHUDInterface.h"
#include "Narrative/NoteData.h"
#include "MainHUD.generated.h"

class UNoteWidget;
class UStatsWidget;
class UDisplayWidget;
class UTitleNoteWidget;
/**
 * 
 */
UCLASS()
class CYBERLIFE_API AMainHUD : public AHUD, public IMainHUDInterface
{
	GENERATED_BODY()
	
public:
	virtual void SwitchDisplay_Implementation() override;
	
	virtual void ShowDisplay();

	virtual void HideDisplay();
	
	virtual void ChangeHealth_Implementation(const float Magnitude, const float NewValue, const float OldValue) override;

	virtual void ChangeStamina_Implementation(const float Magnitude, const float NewValue, const float OldValue) override;

protected:
	
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="GameUI")
	TSubclassOf<UDisplayWidget> DisplayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UDisplayWidget> DisplayWidget;

	UPROPERTY(EditDefaultsOnly, Category="GameUI")
	TSubclassOf<UUserWidget> PointScreenWidgetClass{nullptr};
	
	UPROPERTY(EditDefaultsOnly, Category="GameUI")
	TSubclassOf<UStatsWidget> StatsWidgetClass{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="GameUI|Note")
	TSubclassOf<UNoteWidget> NoteWidgetClass{nullptr};

	UPROPERTY()
	TObjectPtr<UStatsWidget> StatsWidget{nullptr};

	UFUNCTION()
	void OnNoteWidgetClose();
	
	void CreateNoteWidget(const FNoteData& InNote);
	
	UFUNCTION()
	void OnAddedNote(const FNoteData& InNote);
	
};