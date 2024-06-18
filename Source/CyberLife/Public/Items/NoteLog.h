// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Narrative/NoteData.h"
#include "NoteLog.generated.h"

/**
 * 
 */
UCLASS()
class CYBERLIFE_API ANoteLog : public AInteractableActor
{
	GENERATED_BODY()

public:
	virtual void Interact_Implementation(UInteractionComponent* InteractionComponent) override;

protected:
	UPROPERTY(EditAnywhere, meta=(RowType=NoteData))
	FDataTableRowHandle NoteData;
	
};