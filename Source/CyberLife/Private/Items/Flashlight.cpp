// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Flashlight.h"

void AFlashlight::Interact(UInteractionComponent* InteractionComponent)
{
	Super::Interact(InteractionComponent);

	Destroy();
}
