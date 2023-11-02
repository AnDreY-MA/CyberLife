// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSaver.generated.h"

/**
 * 
 */
UCLASS()
class CYBERLIFE_API UGameSaver : public USaveGame
{
	GENERATED_BODY()

public:
	void SavePlayer(FTransform PlayerPos);

	FTransform GetPlayerPosition() const { return PlayerPosition; }

private:
	
	FTransform PlayerPosition;
	
};
