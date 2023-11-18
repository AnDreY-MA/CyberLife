// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NoteData.h"
#include "LogBook.generated.h"

class UBorder;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDataUpdated, FNoteData, NoteData);

class UUserWidget;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERLIFE_API ULogBook : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULogBook();

	FOnDataUpdated OnDataUpdated;
	
	void AddNote(const FNoteData& Note);

	TSubclassOf<UUserWidget> GetTitleNoteWidget() { return TileNoteWidgetclass; }
	
protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> TileNoteWidgetclass;

private:
	UPROPERTY(VisibleAnywhere)
	TArray<FNoteData> Notes;

	
};
