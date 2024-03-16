// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimInterface.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class ACharacter;

UCLASS()
class CYBERLIFE_API UPlayerAnimInstance : public UAnimInstance, public ICharacterAnimInterface
{
	GENERATED_BODY()

public:

	virtual void EquipWeapon_Implementation(EWeaponType InWeaponType) override;

private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	EWeaponType WeaponType{EWeaponType::None};

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<ACharacter> OwnerCharacter{nullptr};

	virtual void NativeBeginPlay() override;
	
};
