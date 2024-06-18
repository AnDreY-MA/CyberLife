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

	for(TSubclassOf<UGameplayAbilityBase>& Ability : InputAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->GetAbilityID()), GetOwner()));
	}

	for(TSubclassOf<UGameplayAbility>& Ability : DefaultAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE,GetOwner()));
	}

	for(const auto& Config : AttributeConfigs)
	{
		if(Config.AttributeClass && Config.AttributeTable)
		{
			InitStats(Config.AttributeClass.Get(), Config.AttributeTable);
		}
	}

}

void UAbilityComponentBase::ActivateAbility(const EAbilityInputID& InputID)
{
	AbilityLocalInputPressed(static_cast<int32>(InputID));

}

void UAbilityComponentBase::ReleaseAbility(const EAbilityInputID& InputID)
{
	AbilityLocalInputReleased(static_cast<int32>(InputID));

}