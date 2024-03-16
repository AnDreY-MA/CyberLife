// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemy/EnemyMovementMode.h"
#include "UObject/Interface.h"
#include "PatrolerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPatrolerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CYBERLIFE_API IPatrolerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Movement")
	float SetMovementMode(const EEnemyMovementMode InMovementMode);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Patrol")
	FVector GetSplinePointPosition() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Patrol")
	AActor* GetPatrolRoute() const;

};