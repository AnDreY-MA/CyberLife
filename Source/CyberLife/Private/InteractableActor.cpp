#include "InteractableActor.h"

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(MeshComponent);

	MeshComponent->CustomDepthStencilValue = 1;

}

void AInteractableActor::Interact(UInteractionComponent* InteractionComponent)
{
	
}

void AInteractableActor::ShowOutline()
{
	MeshComponent->SetRenderCustomDepth(true);
}

void AInteractableActor::HideOutline()
{
	MeshComponent->SetRenderCustomDepth(false);

}
