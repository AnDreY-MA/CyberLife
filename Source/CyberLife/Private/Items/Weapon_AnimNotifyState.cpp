#include "Items/Weapon_AnimNotifyState.h"

#include "Items/MeeleWeapon.h"
#include "Player/InteractionComponent.h"
#include "Player/PlayerCharacter.h"

void UWeapon_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
										  float TotalDuration)
{
	auto* MeeleWeapon = GetMeeleWeapon(MeshComp);
	if (!MeeleWeapon) return;
	
	MeeleWeapon->TriggerAttack();
	
}

void UWeapon_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	auto* MeeleWeapon = GetMeeleWeapon(MeshComp);
	if (!MeeleWeapon) return;
	
	MeeleWeapon->StopTrigger();
}

AMeeleWeapon* UWeapon_AnimNotifyState::GetMeeleWeapon(const USkeletalMeshComponent* MeshComp) const
{
	const auto* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (!PlayerCharacter) return nullptr;
	const auto* InteractionComponent = PlayerCharacter->GetInteractionComponent();
	auto* MeeleWeapon = Cast<AMeeleWeapon>(InteractionComponent->GetWaepon());

	return MeeleWeapon;
}
