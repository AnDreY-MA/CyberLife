// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"

#include "Components/SphereComponent.h"
#include "Items/InventoryComponent.h"
#include "Items/ItemObject.h"
#include "Player/InteractionComponent.h"
#include "Player/PlayerCharacter.h"

AItem::AItem()
{
	
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	if(!IsValid(ItemObject))
	{
		InitItemObject();
	}
}

void AItem::InitItemObject()
{
	ItemObject = NewObject<UItemObject>();
	ItemObject->Dimensions = ItemData.Dimensions;
	ItemObject->Icon = ItemData.Icon;
	ItemObject->IconRotated = ItemData.IconRotated;
	ItemObject->ItemClass = ItemData.ItemClass;
	ItemObject->BPItemName = ItemData.BPObjectName;
}

void AItem::SetItemObject(UItemObject* ItemObjectParam)
{
	ItemObject = ItemObjectParam;
}

void AItem::Interact(UInteractionComponent* InteractionComponent)
{
	InteractionComponent->GetInventory()->AddItem(ItemObject);
	Destroy();
	
}