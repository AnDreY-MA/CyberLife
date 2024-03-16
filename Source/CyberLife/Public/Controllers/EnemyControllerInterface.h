// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CYBERLIFE_API IEnemyControllerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Attack")
	void Attack();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Attack")
	AActor* GetAttackTarget() const;
	
};