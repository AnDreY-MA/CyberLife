// Fill out your copyright notice in the Description page of Project Settings.


#include "Narrative/LogBook.h"

ULogBook::ULogBook()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void ULogBook::AddNote(const FNoteData& Note)
{
	Notes.Add(Note);

	OnDataUpdated.Broadcast(Note);
}


