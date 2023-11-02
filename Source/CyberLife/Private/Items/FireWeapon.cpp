// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FireWeapon.h"

#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Items/Bullet.h"

void AFireWeapon::Attack(AActor* OwnerActor)
{
	
	const USkeletalMeshSocket* BarrelSocket = WeaponMesh->GetSocketByName(FName("BarrelSocket"));
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	const auto Rotation = OwnerActor->FindComponentByClass<UCameraComponent>()->GetComponentRotation();
	auto* Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, BarrelSocket->GetSocketLocation(WeaponMesh), Rotation);
	Bullet->SetDamatePoint(DamagePower);
	
}

void AFireWeapon::BeginPlay()
{
	Super::BeginPlay();
}
