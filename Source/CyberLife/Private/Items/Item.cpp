// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"

#include "Items/InventoryComponent.h"
#include "Components/InteractionComponent.h"
#include "Items/InventoryComponentInterface.h"
#include "Items/Data/ItemData.h"

AItem::AItem()
{
	
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	if(!IsValid(ItemData))
	{
		InitItemObject();
	}
}

void AItem::InitItemObject()
{

}

void AItem::SetItemObject(UItemData* ItemObjectParam)
{
	ItemData = ItemObjectParam;
}

void AItem::Interact_Implementation(UInteractionComponent* InteractionComponent)
{
	if(auto* InteractionActor = InteractionComponent->GetOwner(); InteractionActor->Implements<UInventoryComponentInterface>())
	{
		if(IInventoryComponentInterface::Execute_GetInventoryComponent(InteractionActor)->TryAddItem(ItemData))
		{
			Destroy();
		}
		else
		{
		}
	}
	
}