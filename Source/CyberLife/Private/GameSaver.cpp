// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSaver.h"

void UGameSaver::SavePlayer(FTransform PlayerPos)
{
	PlayerPosition = {};
	PlayerPosition = PlayerPos;
}
