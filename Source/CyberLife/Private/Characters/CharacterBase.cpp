// Mamont Protaction copy rights


#include "Characters/CharacterBase.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	if(const IAbilitySystemInterface* CurrentController{Cast<IAbilitySystemInterface>(GetController())})
	{
		return CurrentController->GetAbilitySystemComponent();
	}

	return nullptr;
}
