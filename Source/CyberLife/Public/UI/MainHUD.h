// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UStatsWidget;
class UDisplayWidget;
class UTitleNoteWidget;
/**
 * 
 */
UCLASS()
class CYBERLIFE_API AMainHUD : public AHUD
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UDisplayWidget* DisplayWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTitleNoteWidget> TileNoteWidgetClass;

private:
	UPROPERTY(EditDefaultsOnly, Category="GameUI")
	TSubclassOf<UStatsWidget> StatsWidgetClass{nullptr};
	
	TUniquePtr<UStatsWidget> StatsWidget{nullptr};
	
};