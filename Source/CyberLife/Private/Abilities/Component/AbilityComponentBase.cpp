// ]
// \mont Protaction copy rights


#include "Abilities/Component/AbilityComponentBase.h"

#include "Abilities/Abilities/GameplayAbilityBase.h"

UAbilityComponentBase::UAbilityComponentBase()
{
	
}

void UAbilityComponentBase::BeginPlay()
{
	Super::BeginPlay();

	for(TSubclassOf<UGameplayAbilityBase>& Ability : DefaultAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->GetAbilityID()), GetOwner()));
	}

	for(const auto& Config : AttributeConfigs)
	{
		if(Config.AttributeClass && Config.AttributeTable)
		{
			InitStats(Config.AttributeClass.Get(), Config.AttributeTable);
		}
	}

}

void UAbilityComponentBase::ActivateAbility(const EAbilityInputID InputID)
{
	AbilityLocalInputPressed(static_cast<int32>(InputID));
}