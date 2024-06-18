// Mamont Protaction copy rights


#include "Abilities/Attributes/CharacterAttributeSet.h"
#include "GameplayEffectExtension.h"


void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		if(OnHealthChanged.IsBound())
		{
			const float OldValue = GetHealth() - Data.EvaluatedData.Magnitude;
			OnHealthChanged.Broadcast(GetHealth(), OldValue, Data.EvaluatedData.Magnitude);
		}
	}

	if(Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0, GetMaxStamina()));
		if(OnStaminaChanged.IsBound())
		{
			const float OldValue = GetStamina() - Data.EvaluatedData.Magnitude;
			OnStaminaChanged.Broadcast(GetStamina(), OldValue, Data.EvaluatedData.Magnitude);
		}
	}

}