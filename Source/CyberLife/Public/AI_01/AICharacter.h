#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class CYBERLIFE_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAICharacter();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess= "true"))
	float MaxHealth;

	UPROPERTY()
	float CurrentHealth;
	
	UPROPERTY(EditDefaultsOnly)
	USoundBase* TakeDamageSound;

private:
	virtual void BeginPlay() override;

	virtual void ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser) override;
};
