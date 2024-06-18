// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Abilities/AbilityInputID.h"
#include "AbilityComponentBase.generated.h"

class UGameplayAbilityBase;

USTRUCT(Blueprintable, BlueprintType)
struct FAttributeConfig
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category="Attribute Config")
	TSubclassOf<UAttributeSet> AttributeClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Attribute Config")
	TObjectPtr<UDataTable> AttributeTable;
};

UCLASS()
class CYBERLIFE_API UAbilityComponentBase : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UAbilityComponentBase();

	virtual void BeginPlay() override;

	virtual void ActivateAbility(const EAbilityInputID& InputID);
	virtual void ReleaseAbility(const EAbilityInputID& InputID);
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbilityBase>> InputAbilities;
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category="Attributes")
	TArray<FAttributeConfig> AttributeConfigs;
	
};