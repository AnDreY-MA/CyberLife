// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FireWeapon.h"

#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine/StaticMeshSocket.h"
#include "Items/Bullet.h"

void AFireWeapon::Attack(AActor* OwnerActor)
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	const auto Rotation = OwnerActor->FindComponentByClass<UCameraComponent>()->GetComponentRotation();
	auto* Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, MeshComponent->GetSocketLocation(FName("BarrelSocket")), Rotation);
	Bullet->SetDamatePoint(DamagePower);
	
}

void AFireWeapon::BeginPlay()
{
	Super::BeginPlay();
}
