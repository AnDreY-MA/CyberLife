// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Flashlight.h"

#include "Components/InteractionComponent.h"

void AFlashlight::Interact_Implementation(UInteractionComponent* InteractionComponent)
{
	Super::Interact_Implementation(InteractionComponent);
	
	InteractionComponent->OnFlashlightPickUp.Broadcast();
	Destroy();
}