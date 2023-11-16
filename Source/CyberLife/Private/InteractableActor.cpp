#include "InteractableActor.h"

#include "Player/PlayerCharacter.h"

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(MeshComponent);

	MeshComponent->CustomDepthStencilValue = 1;
	MeshComponent->SetRenderCustomDepth(false);

	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractableActor::OnOverlapBegin);
	MeshComponent->OnComponentEndOverlap.AddDynamic(this, &AInteractableActor::OnOverlapEnd);

}

void AInteractableActor::Interact(UInteractionComponent* InteractionComponent)
{
	
}

void AInteractableActor::ToggleFocus(bool Focus)
{
	MeshComponent->SetRenderCustomDepth(Focus);
}

void AInteractableActor::ShowOutline()
{
	MeshComponent->SetRenderCustomDepth(true);
}

void AInteractableActor::HideOutline()
{
	MeshComponent->SetRenderCustomDepth(false);

}

void AInteractableActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Begin"));

	if(OtherComp)
	{
		ToggleFocus(true);
		UE_LOG(LogTemp, Warning, TEXT("Begin"));
	}
}

void AInteractableActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherComp->GetAttachParentActor() == Cast<APlayerCharacter>(OtherActor))
	{
		ToggleFocus(false);
		UE_LOG(LogTemp, Warning, TEXT("Begin"));

	}
}
