#include "Player/PlayerAnimInstance.h"

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	
}

void UPlayerAnimInstance::EquipWeapon()
{
	bEquiped = true;
}

void UPlayerAnimInstance::UnEquipWeapon()
{
	bEquiped = false;
	bEquipedMeeleWeapon = false;
}

void UPlayerAnimInstance::EquipMeeleWeapon()
{
	bEquipedMeeleWeapon = true;
}
