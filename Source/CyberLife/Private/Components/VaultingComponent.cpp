#include "Components/VaultingComponent.h"

#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UVaultingComponent::UVaultingComponent(): VaultWidget(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UVaultingComponent::Vault()
{
	Progress = 0.0f;
	StartingPosition = GetOwner()->GetActorLocation();
	VaultState = EVaultState::EVS_Vaulting;
	
}

void UVaultingComponent::BeginPlay()
{
	Super::BeginPlay();

	auto* Owning = GetOwner()->GetInstigatorController();
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

	auto* Capsule = GetOwner()->GetInstigatorController()->GetCharacter()->GetCapsuleComponent();

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
	GetOwner()->SetActorLocation(NewLocation);

	if (Progress >= 1.0f)
	{
		VaultState = EVaultState::EVS_NotVault;
	}
	
}

FHitResult UVaultingComponent::TraceToVault(UCapsuleComponent* CapsuleComponent) const
{
	FHitResult HitResult;
	const FVector Location = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 40.0f;
	const FVector Start = Location + FVector(0.0, 0.0, CapsuleComponent->GetScaledCapsuleHalfHeight());
	const FVector End = Location - FVector(0.0, 0.0, CapsuleComponent->GetScaledCapsuleHalfHeight());
	FCollisionQueryParams CollisionParams = FCollisionQueryParams::DefaultQueryParam;

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams, FCollisionResponseParams());

	return HitResult;
}

void UVaultingComponent::CheckVault()
{
	if(!VaultWidget) return;
	
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
	if (!UKismetMathLibrary::InRange_FloatFloat(HitResult.Location.Z - HitResult.TraceEnd.Z,
		MinVaultingHeight, MaxVaultingHeight))
	{
		return FVector::ZeroVector;
	}

	if(HitResult.Normal.Z < GetOwner()->GetInstigatorController()->GetCharacter()->GetCharacterMovement()->GetWalkableFloorZ())
	{
		return FVector::ZeroVector;
	}

	const FVector EndLocationLocal = HitResult.Location + FVector(0.0, 0.0, Capsule->GetScaledCapsuleHalfHeight());

	if(!CheckCapsuleCollision(EndLocationLocal + FVector(0.0, 0.0, Capsule->GetScaledCapsuleHalfHeight()),
		Capsule->GetScaledCapsuleHalfHeight(), Capsule->GetScaledCapsuleRadius()))
	{
		return FVector::ZeroVector;
	}
	
	return EndLocationLocal;
}

bool UVaultingComponent::CheckCapsuleCollision(const FVector Center, const float HalfHeight, const float Radius) const
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	TArray<AActor*> OverlappingActors;

	return UKismetSystemLibrary::CapsuleOverlapActors(this, Center, HalfHeight, Radius, ObjectTypes, AActor::StaticClass(),
		TArray<AActor*>(), OverlappingActors);

}