// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LogBook.generated.h"

USTRUCT(BlueprintType)
struct FNoteData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly, meta=(MultiLine=true))
	FText Description;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERLIFE_API ULogBook : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULogBook();

	void AddNote(const FNoteData& Note);

private:
	UPROPERTY()
	TArray<FNoteData> Notes;
};
