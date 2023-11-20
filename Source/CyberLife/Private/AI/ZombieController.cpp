// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ZombieController.h"

#include "Perception/AIPerceptionComponent.h"

AZombieController::AZombieController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
}

void AZombieController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);
}
