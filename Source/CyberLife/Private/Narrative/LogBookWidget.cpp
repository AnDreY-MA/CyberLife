// Fill out your copyright notice in the Description page of Project Settings.


#include "Narrative/LogBookWidget.h"

#include "Components/MultiLineEditableTextBox.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Narrative/LogBook.h"
#include "Narrative/TitleNoteWidget.h"

void ULogBookWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	NoteText->SetVisibility(ESlateVisibility::Collapsed);

}

void ULogBookWidget::Show()
{
	const auto* LogBook {GetOwningPlayer()->FindComponentByInterface<ULogBookInterface>()};
	
	if(!LogBook) return;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *LogBook->GetName());

	
	const auto Notes {ILogBookInterface::Execute_GetNotes(LogBook)};
	if(Notes.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Empty"));
	}
	for(auto Note : Notes)
	{
		auto* TitleNote {CreateWidget<UTitleNoteWidget>(GetOwningPlayer(), TitleNoteWidgetClass)};
		TitleNote->Init(Note);
		TitleNote->OnShowNoteData.AddDynamic(this, &ULogBookWidget::ReadNote);
		UE_LOG(LogTemp, Warning, TEXT("LOGBOOKWIDGET"));

		Content->AddChild(TitleNote);
	}
}

void ULogBookWidget::Hide()
{
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
	Description->SetText(NoteData.Description);
	NoteText->SetVisibility(ESlateVisibility::Visible);
}

void ULogBookWidget::HideNote()
{
	Content->SetVisibility(ESlateVisibility::Visible);
	NoteText->SetVisibility(ESlateVisibility::Collapsed);

}