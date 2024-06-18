#include "Components/InteractionComponent.h"

#include "interactable.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Items/GrabObjectInterface.h"
#include "Items/NoteLog.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

UInteractionComponent::UInteractionComponent() :
	InteractDistance(0.0f), ForceThrow(0)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TraceInteract();

	if(HoldingObject.Get())
	{
		PhysicsHandle->SetTargetLocationAndRotation(DefaultGrabObjectLocation->GetComponentLocation(),
			DefaultGrabObjectLocation->GetComponentRotation());
	}

}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UInteractionComponent::Init(UPhysicsHandleComponent* PhysicsHandleComponent, UArrowComponent* DefaultLocation,
                                 UCameraComponent* CameraComponentParam)
{
	PhysicsHandle = PhysicsHandleComponent;
	DefaultGrabObjectLocation = DefaultLocation;
	CameraComponent = CameraComponentParam;
}

void UInteractionComponent::Interact()
{
	if(!HoldingObject.Get())
	{
		TraceForObject();
	}
	else if (HoldingObject.Get())
	{
		DropObject();
	}
}

void UInteractionComponent::PickUpNote(const FNoteData& NoteData)
{
	OnNoteLogPickUp.Broadcast(NoteData);
}

bool UInteractionComponent::IsHoldingObject() const
{
	return IsValid(HoldingObject.Get());
}

void UInteractionComponent::ThrowObject()
{
	const FVector Forward = GetOwner()->GetActorForwardVector() * ForceThrow * HoldingObject->GetMass();
	HoldingObject->AddImpulse(Forward);
	DropObject();
}

void UInteractionComponent::TraceForObject()
{
	const FVector Start = CameraComponent->GetComponentLocation();
	
	const FVector End = CameraComponent->GetForwardVector() * InteractDistance + Start;
	FHitResult HitResult;

	TArray<AActor*> ActorsIgnore;
	ActorsIgnore.Add(GetOwner());
	if(UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, InteractableTypes, true, ActorsIgnore, EDrawDebugTrace::None, HitResult, true))
	{
		if(auto* Interactabler = HitResult.GetActor(); Interactabler->Implements<UInteractable>()
			&& !Interactabler->Implements<UGrabObjectInterface>())
		{
			IInteractable::Execute_Interact(Interactabler, this);
			IInteractable::Execute_ToggleFocus(Interactabler, false);
		}
		else if(Interactabler->Implements<UGrabObjectInterface>())
		{
			GrabObject(HitResult);
		}
		
	}
}

void UInteractionComponent::GrabObject(const FHitResult& HitResult)
{
	PhysicsHandle->GrabComponentAtLocationWithRotation(HitResult.GetComponent(), "",
			HitResult.Component->GetComponentLocation(), HitResult.Component->GetComponentRotation());
	HoldingObject = HitResult.GetComponent();
	HoldingObject->SetCollisionResponseToChannel(ECC_Destructible, ECR_Ignore);
	SetComponentTickEnabled(true);

	
}

void UInteractionComponent::DropObject()
{
	HoldingObject->SetCollisionResponseToChannel(ECC_Destructible, ECR_Block);
	PhysicsHandle->ReleaseComponent();
	HoldingObject = nullptr;
}

void UInteractionComponent::TraceInteract()
{
	const FVector Start = CameraComponent->GetComponentLocation();
	const FVector End = CameraComponent->GetForwardVector() * InteractDistance + Start;
	FHitResult HitResult;

	TArray<AActor*> ActorsIgnore;
	ActorsIgnore.Add(GetOwner());
	if(UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, InteractableTypes, true, ActorsIgnore,
		EDrawDebugTrace::None, HitResult, true))
	{
		if(auto* HitActor{HitResult.GetActor()}; HitActor)
		{
			if(HitActor->Implements<UInteractable>())
			{
				FocusedActor = HitActor;
				IInteractable::Execute_ToggleFocus(HitActor, true);
			}
		}
	}
	else
	{
		if(FocusedActor)
		{
			IInteractable::Execute_ToggleFocus(FocusedActor, false);
			FocusedActor = nullptr;
		}
	}
}