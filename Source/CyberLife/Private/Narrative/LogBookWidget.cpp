// Fill out your copyright notice in the Description page of Project Settings.


#include "Narrative/LogBookWidget.h"

#include "Components/MultiLineEditableTextBox.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Narrative/LogBook.h"
#include "Narrative/TitleNoteWidget.h"

void ULogBookWidget::Init(ULogBook* InLogBook)
{
	TitleNoteWidgetClass = InLogBook->GetTitleNoteWidget();
	InLogBook->OnDataUpdated.AddDynamic(this, &ULogBookWidget::AddNote);

	NoteText->SetVisibility(ESlateVisibility::Collapsed);
}


void ULogBookWidget::AddNote(FNoteData NoteData)
{
	if(auto* TitleNote = Cast<UTitleNoteWidget>(CreateWidget<UUserWidget>(GetWorld(), TitleNoteWidgetClass)))
	{
		TitleNote->Init(NoteData);
		TitleNote->OnShowNoteData.AddDynamic(this, &ULogBookWidget::ReadNote);
		Content->AddChild(TitleNote);
	}
	
}

void ULogBookWidget::ReadNote(FNoteData NoteData)
{
	Content->SetVisibility(ESlateVisibility::Collapsed);
	NameText->SetText(FText::FromString(NoteData.Name));
	Description->SetText(NoteData.Description);
	NoteText->SetVisibility(ESlateVisibility::Visible);
}

void ULogBookWidget::HideNote()
{
	Content->SetVisibility(ESlateVisibility::Visible);
	NoteText->SetVisibility(ESlateVisibility::Collapsed);
}
