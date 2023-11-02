// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StatsWidget.h"

#include "Player/PlayerCharacter.h"

void UStatsWidget::ChangeHealth(const float Value)
{
	HealthText->SetText(FText::AsNumber(Value));
	
}

void UStatsWidget::Setup(APlayerCharacter* PlayerCharacter)
{
	PlayerCharacter->OnHealthChanged.AddDynamic(this, &UStatsWidget::ChangeHealth);
}
