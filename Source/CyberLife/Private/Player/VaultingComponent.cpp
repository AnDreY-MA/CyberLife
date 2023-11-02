#include "Player/VaultingComponent.h"

#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UVaultingComponent::UVaultingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UVaultingComponent::Vault()
{
	Progress = 0.0f;
	StartingPosition = OwningCharacter->GetActorLocation();
	VaultState = EVaultState::EVS_Vaulting;
	
}

void UVaultingComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningCharacter = Cast<ACharacter>(GetOwner());

	auto* Owning = GetOwner()->GetInstigator()->GetController();
	auto* Controller = Cast<APlayerController>(Owning);
	VaultWidget = CreateWidget(Controller, VaultWidgetClass);
}

void UVaultingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (VaultState)
	{
	case EVaultState::EVS_Vaulting:
		VaultTick(DeltaTime);
		break;
	case EVaultState::EVS_NotVault:
		CheckVault();
		break;
	}
}

bool UVaultingComponent::CanVault()
{
	if(VaultState != EVaultState::EVS_NotVault) return false;

	auto* Capsule = OwningCharacter->GetCapsuleComponent();

	FHitResult HitResult = TraceToVault(Capsule);
	if(!HitResult.bBlockingHit) return false;

	if(CanVaultToHit(Capsule, HitResult) != FVector::ZeroVector)
	{
		EndPosition = CanVaultToHit(Capsule, HitResult);
		return true;
	}
	
	return false;
}

void UVaultingComponent::VaultTick(const float DeltaSeconds)
{
	const float ProgressValue = Progress + DeltaSeconds / VaultSpeed;
	Progress = FMath::Clamp(ProgressValue, 0.0f, 1.0f);
	const FVector NewLocation = FMath::Lerp(StartingPosition, EndPosition, Progress);
	OwningCharacter->SetActorLocation(NewLocation);

	if (Progress >= 1.0f)
	{
		VaultState = EVaultState::EVS_NotVault;
	}
	
}

FHitResult UVaultingComponent::TraceToVault(UCapsuleComponent* CapsuleComponent)
{
	FHitResult HitResult;
	const FVector Location = OwningCharacter->GetActorLocation() + OwningCharacter->GetActorForwardVector() * 40.0f;
	const FVector Start = Location + FVector(0.0, 0.0, CapsuleComponent->GetScaledCapsuleHalfHeight());
	const FVector End = Location - FVector(0.0, 0.0, CapsuleComponent->GetScaledCapsuleHalfHeight());
	FCollisionQueryParams CollisionParams = FCollisionQueryParams::DefaultQueryParam;

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams, FCollisionResponseParams());

	return HitResult;
}

void UVaultingComponent::CheckVault()
{
	if(CanVault())
	{
		if(!VaultWidget->IsInViewport())
		{
			VaultWidget->AddToViewport();
		}
	}
	else
	{
		if(VaultWidget->IsInViewport())
		{
			VaultWidget->RemoveFromParent();
		}
	}
}

FVector UVaultingComponent::CanVaultToHit(UCapsuleComponent* Capsule, const FHitResult& HitResult)
{
	FVector EndLocationLocal = {0.0f, 0.0f, 0.0f};

	if (!UKismetMathLibrary::InRange_FloatFloat(	HitResult.Location.Z - HitResult.TraceEnd.Z,
		MinVaultingHeight, MaxVaultingHeight))
	{
		return FVector::ZeroVector;
	}

	if(HitResult.Normal.Z < OwningCharacter->GetCharacterMovement()->GetWalkableFloorZ())
	{
		return FVector::ZeroVector;
	}

	EndLocationLocal = HitResult.Location + FVector(0.0, 0.0, Capsule->GetScaledCapsuleHalfHeight());

	if(!CheckCapsuleCollision(EndLocationLocal + FVector(0.0, 0.0, Capsule->GetScaledCapsuleHalfHeight()),
		Capsule->GetScaledCapsuleHalfHeight(), Capsule->GetScaledCapsuleRadius()))
	{
		return FVector::ZeroVector;
	}
	
	return EndLocationLocal;
}

bool UVaultingComponent::CheckCapsuleCollision(FVector Center, float HalfHeight, float Radius)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	TArray<AActor*> OverlappingActors;

	return UKismetSystemLibrary::CapsuleOverlapActors(this, Center, HalfHeight, Radius, ObjectTypes, AActor::StaticClass(),
		TArray<AActor*>(), OverlappingActors);
}
