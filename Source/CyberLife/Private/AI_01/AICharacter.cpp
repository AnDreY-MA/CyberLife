// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_01/AICharacter.h"

// Sets default values
AAICharacter::AAICharacter() :
	MaxHealth(100.0f)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->DestroyComponent();

}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void AAICharacter::ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator,
	AActor* DamageCauser)
{
	Super::ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);

	CurrentHealth -= DamageTaken;
	if(CurrentHealth >= 0.0f)
	{
		Destroy();
	}
}
