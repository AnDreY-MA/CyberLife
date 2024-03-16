// Mamont Protaction copy rights


#include "Abilities/Abilities/FlashlightAbility.h"

#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"

void UFlashlightAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if(const auto* Avatar {ActorInfo->AvatarActor.Get()}; Avatar)
	{
		if(auto* Flashlight {Avatar->FindComponentByClass<USpotLightComponent>()}; Flashlight)
		{
			Flashlight->SetIntensity(Intensity);
			Flashlight->SetActive(!Flashlight->IsActive());
			UGameplayStatics::PlaySound2D(GetWorld(), FlashlightSound);
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}