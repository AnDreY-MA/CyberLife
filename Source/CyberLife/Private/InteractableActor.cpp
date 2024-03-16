#include "InteractableActor.h"

#include "GameFramework/Character.h"

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(MeshComponent);

	MeshComponent->CustomDepthStencilValue = 1;
	MeshComponent->SetRenderCustomDepth(false);

}

void AInteractableActor::Interact_Implementation(UInteractionComponent* InteractionComponent)
{
	
}

void AInteractableActor::ToggleFocus_Implementation(const bool Focus)
{
	MeshComponent->SetRenderCustomDepth(Focus);
}