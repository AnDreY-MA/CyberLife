// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHUD.h"
#include "UI/StatsWidget.h"
#include "Blueprint/UserWidget.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	if(StatsWidgetClass)
	{
		StatsWidget.Reset(CreateWidget<UStatsWidget>(GetOwningPlayerController(), StatsWidgetClass));
	}
	
}
