// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DisplayWidget.h"

#include "Narrative/LogBookWidget.h"
#include "UI/InventoryGridWidget.h"

void UDisplayWidget::Init(UInventoryComponent* Inventory, const float TileSize)
{
	check(Inventory);
	InventoryComponent = Inventory;
	InventoryGridWidgetBP->Init(Inventory, TileSize);
}

void UDisplayWidget::Show()
{
	LogBookWidget->Show();

}

void UDisplayWidget::RemoveFromParent()
{
	LogBookWidget->RemoveFromParent();
	
	Super::RemoveFromParent();
}