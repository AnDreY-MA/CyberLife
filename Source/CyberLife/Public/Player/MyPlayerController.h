// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UGameSaver;
class APlayerCharacter;
class UInputMappingContext;
class UInputAction;
class UStatsWidget;
class UInventoryWidget;

UCLASS()
class CYBERLIFE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PointScreen;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> Stats;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UStatsWidget* StatsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InventoryUI", meta=(AllowPrivateAccess))
	TSubclassOf<UUserWidget> InventoryWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InventoryUI", meta=(AllowPrivateAccess))
	UInventoryWidget* ActiveInventoryWidget;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* MappingContext;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* ToggleInventoryAction;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* SaveAction;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* LoadAction;

	UPROPERTY()
	UGameSaver* GameSaver;
	
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void ToggleInventoryWidget();
	void HideInventoryWidget();
	void ShowInventoryWidget();

	void SaveGame();
	void LoadGame();
};
