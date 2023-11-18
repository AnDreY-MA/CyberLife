#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "NoteData.generated.h"

USTRUCT(BlueprintType)
struct FNoteData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly, meta=(MultiLine=true))
	FText Description;
};