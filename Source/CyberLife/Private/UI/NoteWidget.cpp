// Mamont Prodaction copy rights


#include "UI/NoteWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Narrative/NoteData.h"

void UNoteWidget::Init(const FNoteData& InData)
{
	Name.Get()->SetText(FText::FromName(InData.Name));
	Title.Get()->SetText(FText::FromName(InData.Title));
	Description.Get()->SetText(InData.Description);

	CloseButton.Get()->OnPressed.AddDynamic(this, &UNoteWidget::OnCloseButton);
}

void UNoteWidget::OnCloseButton()
{
	RemoveFromParent();
	OnClosed.Broadcast();
}