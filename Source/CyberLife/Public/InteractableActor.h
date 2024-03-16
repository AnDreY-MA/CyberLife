// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

UCLASS()
class CYBERLIFE_API AInteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	AInteractableActor();

	virtual void Interact_Implementation(UInteractionComponent* InteractionComponent) override;

	virtual void ToggleFocus_Implementation(bool Focus) override;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
};
