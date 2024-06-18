// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StatsWidget.h"

#include "Components/ProgressBar.h"

void UStatsWidget::ChangeHealth(const float NewValue, const float OldValue, const float Magnitude)
{
	ChangePercentOnBar(HealthBar, NewValue, OldValue);

}

void UStatsWidget::ChangeStamina(const float NewValue, const float OldValue, float Magnitude)
{
	ChangePercentOnBar(StaminaBar, NewValue, OldValue);
	
}

void UStatsWidget::ChangePercentOnBar(const TObjectPtr<UProgressBar> InBar, const float NewValue, const float OldValue)
{
	const float NewPercent {InBar->GetPercent() - (OldValue - NewValue) / 100};
	InBar->SetPercent(NewPercent);
	
}