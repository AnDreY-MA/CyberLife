#include "Items/Weapon.h"
#include "Items/Data/ItemData.h"
#include "Kismet/GameplayStatics.h"

AWeapon::AWeapon()
{
	
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Interact_Implementation(UInteractionComponent* InteractionComponent)
{
	Super::Interact_Implementation(InteractionComponent);

	UE_LOG(LogTemp, Warning, TEXT("Interact"));
}

void AWeapon::Attack(AActor* OwnerActor)
{
	if (!AttackSound) return;
	UGameplayStatics::PlaySound2D(this, AttackSound);
}

void AWeapon::Equip()
{
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemData->EquipWeapon();
}

void AWeapon::UnEquip()
{
	if(!MeshComponent || !ItemData) return;
	
	ItemData->UnEquipWeapon();

	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	const FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, true);
	MeshComponent->DetachFromComponent(DetachmentTransformRules);

	Destroy();

}