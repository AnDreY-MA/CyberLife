// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class UInteractionComponent;

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CYBERLIFE_API IInteractable
{
	GENERATED_BODY()

public:

	virtual void Interact(UInteractionComponent* InteractionComponent) = 0;
	virtual void ToggleFocus(bool Focus) = 0;

};
