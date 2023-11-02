// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "StatsWidget.generated.h"

class APlayerCharacter;
/**
 * 
 */
UCLASS()
class CYBERLIFE_API UStatsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ChangeHealth(float Value);

	void Setup(APlayerCharacter* PlayerCharacter);
	
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* HealthText;
	
};
