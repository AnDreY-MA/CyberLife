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
public:
	void Init(UInventoryComponent* Inventory, float TileSize);

	void Show();

	virtual void RemoveFromParent() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), meta=(AllowPrivateAccess="true"))
	TObjectPtr<UBorder> BackgroundBorder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), meta=(AllowPrivateAccess="true"))
	TObjectPtr<UBackgroundBlur> BackgroundBlur;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInventoryGridWidget> InventoryGridWidgetBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), meta=(AllowPrivateAccess="true"))
	TObjectPtr<ULogBookWidget> LogBookWidget;
};
