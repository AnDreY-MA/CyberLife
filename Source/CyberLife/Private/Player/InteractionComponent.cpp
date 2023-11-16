#include "Player/InteractionComponent.h"

#include "interactable.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Items/Weapon.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

UInteractionComponent::UInteractionComponent() :
	InteractDistance(0.0f)
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(HoldingObject)
	{
		PhysicsHandle->SetTargetLocationAndRotation(DefaultGrabObjectLocation->GetComponentLocation(),
			DefaultGrabObjectLocation->GetComponentRotation());
	}

}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);


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
	if(!HoldingObject)
	{
		TraceForObject();
	}
	else if (HoldingObject)
	{
		DropObject();
	}
}

bool UInteractionComponent::IsHoldingObject() const
{
	return IsValid(HoldingObject);
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

	if(GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ECC_PhysicsBody))
	{
		if(auto* Interactabler = Cast<IInteractable>(HitResult.GetActor()))
		{
			if (auto* Item = Cast<AItem>(Interactabler))
			{
				Interactabler->Interact(this);
			}
			else
			{
				GrabObject(HitResult);
			}
		}
		
	}
}

void UInteractionComponent::GrabObject(const FHitResult HitResult)
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
	SetComponentTickEnabled(false);
}