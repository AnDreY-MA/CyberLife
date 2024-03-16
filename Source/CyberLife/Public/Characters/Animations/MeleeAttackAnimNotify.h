// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MeleeAttackAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class CYBERLIFE_API UMeleeAttackAnimNotify : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	FGameplayTag TagEvent;
	
};