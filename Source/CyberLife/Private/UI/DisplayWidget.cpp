// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DisplayWidget.h"

#include "Narrative/LogBookWidget.h"
#include "UI/InventoryGridWidget.h"

void UDisplayWidget::Init(UInventoryComponent* Inventory, const float TileSize, ULogBook* LogBook)
{
	check(Inventory);
	InventoryComponent = Inventory;
	InventoryGridWidgetBP->Init(Inventory, TileSize);
	LogBookWidget->Init(LogBook);
}
