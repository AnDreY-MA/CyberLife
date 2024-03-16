// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatComponentInterface.generated.h"

class UCombatComponent;

UINTERFACE(MinimalAPI)
class UCombatComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CYBERLIFE_API ICombatComponentInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat Component Interface")
	UCombatComponent* GetCombatComponent();

};