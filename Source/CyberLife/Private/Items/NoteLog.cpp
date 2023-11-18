// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NoteLog.h"

#include "Player/InteractionComponent.h"

void ANoteLog::Interact(UInteractionComponent* InteractionComponent)
{
	Super::Interact(InteractionComponent);

	InteractionComponent->PickUpNote(NoteData);
	Destroy();
}
