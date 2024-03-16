// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "StateControlInterface.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class CYBERLIFE_API ACharacterBase : public ACharacter, public IStateControlInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UPROPERTY(EditDefaultsOnly, Category="State Tag")
	FGameplayTagContainer StatesContainer{};

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UDataTable> CombatMontageTable;
};