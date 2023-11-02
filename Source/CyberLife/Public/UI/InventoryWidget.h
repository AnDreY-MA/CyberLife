// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Border.h"
#include "InventoryWidget.generated.h"

class UInventoryComponent;
class UInventoryGridWidget;

UCLASS()
class CYBERLIFE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UBorder* BackgroundBorder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UBackgroundBlur* BackgroundBlur;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UInventoryGridWidget* InventoryGridWidgetBP;

public:
	void Init(UInventoryComponent* Inventory, float TileSize);

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UInventoryComponent* InventoryComponent;
};
