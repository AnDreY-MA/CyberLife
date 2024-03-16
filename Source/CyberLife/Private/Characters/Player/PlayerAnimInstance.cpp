#include "Characters/Player/PlayerAnimInstance.h"

#include "GameFramework/Character.h"

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());

}

void UPlayerAnimInstance::EquipWeapon_Implementation(EWeaponType InWeaponType)
{
	WeaponType = InWeaponType;
}