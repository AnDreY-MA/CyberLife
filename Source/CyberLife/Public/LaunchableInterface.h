// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LaunchableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULaunchableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CYBERLIFE_API ILaunchableInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Launchable Interface")
	void Launch();
	
};