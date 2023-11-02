// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryGridWidget.h"

#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Items/InventoryComponent.h"
#include "Items/ItemObject.h"

void UInventoryGridWidget::Init(UInventoryComponent* Inventory, const float SizeTile)
{
	InventoryComponent = Inventory;
	TileSize = SizeTile;
	CreateSlotGrid();
	CreateLineSegemnts();
	OnInit();
}

void UInventoryGridWidget::CreateLineSegemnts()
{
	float X = 0.0f;
	for (auto I = 0; I <= InventoryComponent->GetColumns(); ++I)
	{
		X = I * TileSize;

		FLine NewLine = {FVector2D{X, 0.0f},
			FVector2D {X, InventoryComponent->GetRows() * TileSize}};
		Lines.Add(NewLine);
	}

	float Y = 0.0f;
	for (auto I = 0; I <= InventoryComponent->GetRows(); ++I)
	{
		Y = I * TileSize;

		FLine NewLine = {FVector2D{0.0f, Y},
			FVector2D {InventoryComponent->GetColumns() * TileSize, Y}};
		Lines.Add(NewLine);
	}
}

void UInventoryGridWidget::CreateSlotGrid() const
{
	auto* SlotGrid = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridBorder);
	const auto SizeX = InventoryComponent->GetColumns() * TileSize;
	const auto SizeY = InventoryComponent->GetRows() * TileSize;
	SlotGrid->SetSize(FVector2D{SizeX, SizeY});
}

UItemObject* UInventoryGridWidget::GetPayload(UDragDropOperation* DragDropOperation) const
{
	if (!IsValid(DragDropOperation)) return nullptr;

	auto* ItemObject = Cast<UItemObject>(DragDropOperation->Payload);
	return ItemObject;
}
