// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NoteWidget.generated.h"

class UButton;
struct FNoteData;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClosed);

UCLASS()
class CYBERLIFE_API UNoteWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	FOnClosed OnClosed;
	
	void Init(const FNoteData& InData);

private:
	UPROPERTY(meta=(BindWidget), meta=(AllowPrivateAccess="true"))
	TObjectPtr<UTextBlock> Title;
	UPROPERTY(meta=(BindWidget), meta=(AllowPrivateAccess="true"))
	TObjectPtr<UTextBlock> Name;
	UPROPERTY(meta=(BindWidget), meta=(AllowPrivateAccess="true"))
	TObjectPtr<UTextBlock> Description;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), meta=(AllowPrivateAccess="true"))
	TObjectPtr<UButton> CloseButton;

	UFUNCTION()
	void OnCloseButton();
	
};