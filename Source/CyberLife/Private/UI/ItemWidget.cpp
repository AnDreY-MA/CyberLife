// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Items/ItemObject.h"

void UItemWidget::Init(UItemObject* ItemObjectParam, float FloatSizeParam)
{
	ItemObject = ItemObjectParam;
	TileSize =FloatSizeParam;

	Refresh();
}

void UItemWidget::Refresh()
{
	Size = {ItemObject->GetDimensions().X * TileSize, ItemObject->GetDimensions().Y * TileSize};

	BackgroundSizeBox->SetWidthOverride(Size.X);
	BackgroundSizeBox->SetHeightOverride(Size.Y);
	UWidgetLayoutLibrary::SlotAsCanvasSlot(ItemImage)->SetSize(Size);
}
