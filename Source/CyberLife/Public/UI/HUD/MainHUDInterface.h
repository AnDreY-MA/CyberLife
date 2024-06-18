// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MainHUDInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMainHUDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CYBERLIFE_API IMainHUDInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Main HUD| Display Widget")
	void SwitchDisplay();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Main HUD| Stats Widget")
	void ChangeHealth(const float Magnitude, const float NewValue, const float OldValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Main HUD| Stats Widget")
	void ChangeStamina(const float Magnitude, const float NewValue, const float OldValue);
	
};