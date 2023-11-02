#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameScreen.generated.h"

class UStatsWidget;
/**
 * 
 */
UCLASS()
class CYBERLIFE_API UGameScreen : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	UStatsWidget* HealthStat;
};
