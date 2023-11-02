#include "Items/Weapon.h"

#include "Items/ItemObject.h"
#include "Kismet/GameplayStatics.h"

AWeapon::AWeapon()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
	MeshComponent->DestroyComponent(true);
}


void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Interact(UInteractionComponent* InteractionComponent)
{
	Super::Interact(InteractionComponent);
	
}

void AWeapon::Attack(AActor* OwnerActor)
{
	if (!AttackSound) return;
	UGameplayStatics::PlaySound2D(this, AttackSound);
}

void AWeapon::Equip()
{
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemObject->EquipWeapon();
}

void AWeapon::UnEquip()
{
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ItemObject->UnEquipWeapon();
	const FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, true);
	WeaponMesh->DetachFromComponent(DetachmentTransformRules);

}

void AWeapon::ShowOutline()
{
	WeaponMesh->SetRenderCustomDepth(true);
	
}

void AWeapon::HideOutline()
{
	WeaponMesh->SetRenderCustomDepth(false);

}
