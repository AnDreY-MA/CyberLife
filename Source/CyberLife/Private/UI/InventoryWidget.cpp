// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryWidget.h"

#include "UI/InventoryGridWidget.h"

void UInventoryWidget::Init(UInventoryComponent* Inventory, const float TileSize)
{
	InventoryComponent = Inventory;
	InventoryGridWidgetBP->Init(Inventory, TileSize);
}
