// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"


UCLASS()
class CYBERLIFE_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool bEquiped;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool bEquipedMeeleWeapon;

	virtual void NativeBeginPlay() override;

protected:
	UFUNCTION(BlueprintCallable, meta=(BlueprintProtected))
	void EquipWeapon();
	UFUNCTION(BlueprintCallable, meta=(BlueprintProtected))
	void UnEquipWeapon();
	UFUNCTION(BlueprintCallable, meta=(BlueprintProtected))
	void EquipMeeleWeapon();
	
};
