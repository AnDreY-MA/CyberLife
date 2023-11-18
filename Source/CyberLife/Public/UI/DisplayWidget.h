// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Border.h"
#include "DisplayWidget.generated.h"

class ULogBook;
class ULogBookWidget;
class UInventoryComponent;
class UInventoryGridWidget;

UCLASS()
class CYBERLIFE_API UDisplayWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UBorder* BackgroundBorder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UBackgroundBlur* BackgroundBlur;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UInventoryGridWidget* InventoryGridWidgetBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<ULogBookWidget> LogBookWidget;

public:
	void Init(UInventoryComponent* Inventory, float TileSize, ULogBook* LogBook);

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UInventoryComponent* InventoryComponent;
};
