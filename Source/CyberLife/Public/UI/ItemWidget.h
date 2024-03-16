// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UImage;
class USizeBox;
class UBorder;
class UItemObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, UItemData*, ItemObject);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemEquiped, UItemData*, ItemObject);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemUnequiped);
UCLASS()
class CYBERLIFE_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnItemRemoved OnItemRemoved;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnItemEquiped OnItemEquiped;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnItemUnequiped OnItemUnequiped;
	

	UFUNCTION(BlueprintCallable)
	void Init(UItemData* ItemObjectParam, float FloatSizeParam);
	UFUNCTION(BlueprintCallable)
	void Refresh();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UItemData* ItemObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float TileSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	FVector2D Size;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Color", meta=(AllowPrivateAccess))
	FLinearColor HoverColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Color", meta=(AllowPrivateAccess))
	FLinearColor UnHoverColor;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="InputKey", meta=(AllowPrivateAccess))
	FKey DragKey;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="InputKey", meta=(AllowPrivateAccess))
	FKey EquipKey;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UBorder* BackgroundBorder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	USizeBox* BackgroundSizeBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UImage* ItemImage;

	UFUNCTION(BlueprintPure)
	FSlateBrush GetItemImage() const;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
};
