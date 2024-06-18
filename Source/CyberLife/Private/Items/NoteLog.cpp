// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NoteLog.h"

#include "Components/InteractionComponent.h"
#include "Narrative/LogBook.h"

void ANoteLog::Interact_Implementation(UInteractionComponent* InteractionComponent)
{
	if(auto* LogBook {InteractionComponent->GetOwner()->GetInstigatorController()->FindComponentByInterface(ULogBookInterface::StaticClass())};
		LogBook)
	{
		ILogBookInterface::Execute_AddNote(LogBook, *NoteData.GetRow<FNoteData>(""));
	}
	
	Destroy();

}
