// Fill out your copyright notice in the Description page of Project Settings.


#include "Narrative/TitleNoteWidget.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"

void UTitleNoteWidget::Init(const FNoteData& InNoteData)
{
	NoteDataLink = InNoteData;
	Title->SetText(FText::FromString(NoteDataLink.Name));
	SetPadding(FMargin{0.0, 10.0, 0.0, 10.0});
	
}

void UTitleNoteWidget::MouseClick()
{
	OnShowNoteData.Broadcast(NoteDataLink);
	
}