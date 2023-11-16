#pragma once

#include "CoreMinimal.h"
#include "interactable.h"
#include "InteractableActor.h"
#include "ItemData.h"
#include "GameFramework/Actor.h"
#include "Narrative/LogBook.h"
#include "Item.generated.h"

class USphereComponent;

UCLASS()
class CYBERLIFE_API AItem : public AInteractableActor
{
	GENERATED_BODY()
	
public:	
	AItem();

	UItemObject* GetItemObject() { return ItemObject; }

	UFUNCTION(BlueprintCallable)
	void SetItemObject(UItemObject* ItemObjectParam);
	
	void SetItem(UItemObject* ItemObjectParam) { ItemObject = ItemObjectParam;}

	virtual void Interact(UInteractionComponent* InteractionComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	FItemData ItemData;

	UPROPERTY(BlueprintReadWrite)
	UItemObject* ItemObject;

	UPROPERTY(EditDefaultsOnly)
	FNoteData NoteData;
	
	UPROPERTY(EditDefaultsOnly, meta=(RowType="NoteData"))
	FDataTableRowHandle NoteHandle;
	
	virtual void BeginPlay() override;
	
private:
	virtual void InitItemObject();


	
};
