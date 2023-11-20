// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieController.generated.h"

class UAIPerceptionComponent;

UCLASS()
class CYBERLIFE_API AZombieController : public AAIController
{
	GENERATED_BODY()

public:
	AZombieController();
	
protected:

	UPROPERTY(EditDefaultsOnly)
	UAIPerceptionComponent* PerceptionAIComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBehaviorTree* BehaviorTree;

	void BeginPlay() override;

	
};
