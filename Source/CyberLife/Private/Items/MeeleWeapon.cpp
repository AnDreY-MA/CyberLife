#include "Items/MeeleWeapon.h"

#include "Kismet/KismetSystemLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"

void AMeeleWeapon::Attack(AActor* OwnerActor)
{
	Super::Attack(OwnerActor);
	
}

void AMeeleWeapon::StartAttack_Implementation()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMeeleWeapon::OnAttack, 0.05f, true);
}

void AMeeleWeapon::EndAttack_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void AMeeleWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AMeeleWeapon::OnAttack()
{
	FHitResult HitResult;
	const FVector Start = MeshComponent->GetSocketLocation(FName("start"));
	const FVector End = MeshComponent->GetSocketLocation(FName("end"));
	const TArray<TObjectPtr<AActor>> ActorsIngore{GetInstigator()};
	const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{EObjectTypeQuery::ObjectTypeQuery3, ObjectTypeQuery4};
	
	if (UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Start, End, 50.f, ObjectTypes,
		true, ActorsIngore, EDrawDebugTrace::ForDuration, HitResult, true))
	{
		if(auto* HitActor {HitResult.GetActor()}; HitActor)
		{
			FGameplayEventData Payload;
			Payload.Instigator = GetInstigatorController();
			Payload.Target = HitActor;
			Payload.TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(HitActor);
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetInstigatorController(), DamageTag, Payload);
		}

			
	}
	
}