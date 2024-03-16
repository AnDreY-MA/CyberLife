// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "StateControlInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStateControlInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CYBERLIFE_API IStateControlInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="State")
	void Add(const FGameplayTag& InTag);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="State")
	void Remove(const FGameplayTag& InTag);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="State")
	bool Contains(const FGameplayTag& InTag) const;

};