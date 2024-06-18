// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatsWidget.generated.h"

class UProgressBar;
class UVerticalBox;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class CYBERLIFE_API UStatsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ChangeHealth(const float NewValue, const float OldValue, const float Magnitude);
	void ChangeStamina(float NewValue, float OldValue, float Magnitude);

private:

	UPROPERTY(meta=(BindWidget), meta=(AllowPrivateAccess="true"))
	TObjectPtr<UVerticalBox> BoxStats;

	UPROPERTY(meta=(BindWidget), meta=(AllowPrivateAccess="true"))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(meta=(BindWidget), meta=(AllowPrivateAccess="true"))
	TObjectPtr<UProgressBar> StaminaBar;

	void ChangePercentOnBar(TObjectPtr<UProgressBar> InBar, const float NewValue, const float OldValue);
	
};