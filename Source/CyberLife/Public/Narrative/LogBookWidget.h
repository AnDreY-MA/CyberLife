// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NoteData.h"
#include "Blueprint/UserWidget.h"
#include "LogBookWidget.generated.h"

class UMultiLineEditableTextBox;
class UBorder;
class UVerticalBox;
class UTitleNoteWidget;
class UTextBlock;
class ULogBook;
/**
 * 
 */
UCLASS()
class CYBERLIFE_API ULogBookWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	void Show();

	void Hide();
	
protected:

	UPROPERTY(meta=(BindWidget))
	UBorder* Border;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* Content;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* NoteText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* NameText;

	UPROPERTY(meta=(BindWidget))
	UMultiLineEditableTextBox* Description;

	//Вызывается при нажатии на кнопку выхода
	UFUNCTION(BlueprintCallable)
	void HideNote();

private:

	UPROPERTY(EditDefaultsOnly, Category="ItemNote")
	TSubclassOf<UUserWidget> TitleNoteWidgetClass;

	UFUNCTION()
	void AddNote(FNoteData NoteData);

	UFUNCTION()
	void ReadNote(FNoteData NoteData);

	
	
};
