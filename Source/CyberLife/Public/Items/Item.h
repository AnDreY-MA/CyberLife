#pragma once

#include "CoreMinimal.h"
#include "interactable.h"
#include "InteractableActor.h"
#include "ItemData.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;

UCLASS()
class CYBERLIFE_API AItem : public AInteractableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	FItemData ItemData;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UItemObject* ItemObject;
	
	virtual void BeginPlay() override;
private:
	virtual void InitItemObject();

public:
	UFUNCTION(BlueprintCallable)
	void SetItemObject(UItemObject* ItemObjectParam);
	void SetItem(UItemObject* ItemObjectParam) { ItemObject = ItemObjectParam;}

	virtual void Interact(UInteractionComponent* InteractionComponent) override;
	
};
