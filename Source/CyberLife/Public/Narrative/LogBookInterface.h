// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "NoteData.h"
#include "UObject/Interface.h"
#include "LogBookInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULogBookInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CYBERLIFE_API ILogBookInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Log Book Interface")
	void AddNote(const FNoteData& InNoteData);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Log Book Interface")
	TArray<FNoteData> GetNotes() const;
	
};