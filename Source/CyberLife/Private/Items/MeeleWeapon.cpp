#include "Items/MeeleWeapon.h"

#include "Engine/DamageEvents.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DestructibleComponent.h"

void AMeeleWeapon::Attack(AActor* OwnerActor)
{
	Super::Attack(OwnerActor);
	
	TriggerWaepon();
	TriggerAttack();
}

void AMeeleWeapon::TriggerAttack()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMeeleWeapon::OnAttack, 0.05f, true);
}

void AMeeleWeapon::StopTrigger()
{
	UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(this, TimerHandle);
}

void AMeeleWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AMeeleWeapon::OnAttack()
{
	FHitResult HitResult;
	const FVector Start = WeaponMesh->GetSocketLocation(FName("start"));
	const FVector End = WeaponMesh->GetSocketLocation(FName("end"));
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.bDebugQuery = true;
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Camera, CollisionQueryParams))
	{
		const FDamageEvent DamageEvent;
		const float Damage = HitResult.GetActor()->TakeDamage(DamagePower, DamageEvent, nullptr, nullptr);

		HitResult.GetComponent()->AddImpulse(FVector{5.0, 5.0, 5.0} * 5000.0f);
		UE_LOG(LogTemp, Warning, TEXT("DAMAGE %s"), *HitResult.GetActor()->GetName());
			
	}
	
}
