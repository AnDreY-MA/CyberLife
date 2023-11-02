// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Weapon_AnimNotifyState.generated.h"

class AMeeleWeapon;

UCLASS()
class CYBERLIFE_API UWeapon_AnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;

private:
	AMeeleWeapon* GetMeeleWeapon(const USkeletalMeshComponent* MeshComp) const;
};
