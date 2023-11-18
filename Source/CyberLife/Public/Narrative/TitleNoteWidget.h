// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NoteData.h"
#include "Blueprint/UserWidget.h"
#include "TitleNoteWidget.generated.h"

class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowNoteData, FNoteData, NoteData);

/**
 * 
 */
UCLASS()
class CYBERLIFE_API UTitleNoteWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(const FNoteData& InNoteData);

	FOnShowNoteData OnShowNoteData;

	

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Title;

	
	UPROPERTY(meta=(BindWidget))
	UBorder* Border;

	UFUNCTION(BlueprintCallable)
	void MouseClick();


private:
	UPROPERTY()
	FNoteData NoteDataLink;

	
};
