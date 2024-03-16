// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Items/Data/ItemData.h"

void UItemWidget::Init(UItemData* ItemObjectParam, float FloatSizeParam)
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

FSlateBrush UItemWidget::GetItemImage() const
{
	return UWidgetBlueprintLibrary::MakeBrushFromMaterial(ItemObject->GetIcon(), Size.X, Size.Y);
}

void UItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	BackgroundBorder->SetBrushColor(HoverColor);
}

void UItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	BackgroundBorder->SetBrushColor(UnHoverColor);

}

FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, DragKey).NativeReply;
}

FReply UItemWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(InMouseEvent.IsMouseButtonDown(EquipKey))
	{
		if(ItemObject->IsEquiped())
		{
			OnItemUnequiped.Broadcast();
		}
		else
		{
			OnItemEquiped.Broadcast(ItemObject);
		}
	}
	return UWidgetBlueprintLibrary::Handled().NativeReply;
}
