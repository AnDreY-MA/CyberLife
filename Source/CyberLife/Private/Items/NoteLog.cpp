// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NoteLog.h"

#include "Components/InteractionComponent.h"

void ANoteLog::Interact_Implementation(UInteractionComponent* InteractionComponent)
{
	Super::Interact_Implementation(InteractionComponent);

	InteractionComponent->PickUpNote(NoteData);
	Destroy();
}
