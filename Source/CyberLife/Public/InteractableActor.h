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
	// Sets default values for this actor's properties
	AInteractableActor();

	virtual void Interact(UInteractionComponent* InteractionComponent) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UStaticMeshComponent* MeshComponent;

	virtual void ToggleFocus(bool Focus) override;
	
	UFUNCTION(BlueprintCallable, meta=(BlueprintProtected))
	virtual void ShowOutline();
	UFUNCTION(BlueprintCallable, meta=(BlueprintProtected))
	virtual void HideOutline();

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
					  bool bFromSweep, 
					  const FHitResult &SweepResult );

	UFUNCTION( )
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
