// Mamont Protaction copy rights


#include "Abilities/Attributes/CharacterAttributeSet.h"
#include "GameplayEffectExtension.h"


void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("Change Health"));
		
		if(OnHealthChanged.IsBound())
		{
			const float OldValue = GetHealth() - Data.EvaluatedData.Magnitude;
			OnHealthChanged.Broadcast(Data.EvaluatedData.Magnitude, OldValue, GetHealth());
		}
	}
}
