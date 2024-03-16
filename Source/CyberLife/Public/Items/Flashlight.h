// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Flashlight.generated.h"

/**
 * 
 */
UCLASS()
class CYBERLIFE_API AFlashlight : public AInteractableActor
{
	GENERATED_BODY()

public:
	void Interact_Implementation(UInteractionComponent* InteractionComponent) override;
	
};
