#pragma once

#include "CoreMinimal.h"
#include "interactable.h"
#include "InteractableActor.h"
#include "GameFramework/Actor.h"
#include "Narrative/LogBook.h"
#include "Item.generated.h"

class UItemData;
class USphereComponent;

UCLASS()
class CYBERLIFE_API AItem : public AInteractableActor
{
	GENERATED_BODY()
	
public:	
	AItem();

	UItemData* GetItemData() { return ItemData; }

	UFUNCTION(BlueprintCallable)
	void SetItemObject(UItemData* ItemObjectParam);
	
	void SetItem(UItemData* ItemObjectParam) { ItemData = ItemObjectParam;}

	virtual void Interact_Implementation(UInteractionComponent* InteractionComponent) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category="Data")
	TObjectPtr<UItemData> ItemData;

	/*UPROPERTY(EditDefaultsOnly)
	FNoteData NoteData;
	
	UPROPERTY(EditDefaultsOnly, meta=(RowType="NoteData"))
	FDataTableRowHandle NoteHandle;*/
	
	virtual void BeginPlay() override;
	
private:
	virtual void InitItemObject();
	
};