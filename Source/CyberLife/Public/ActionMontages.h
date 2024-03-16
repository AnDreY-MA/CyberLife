#pragma once

#include "CoreMinimal.h"
#include "ActionMontages.generated.h"

USTRUCT(BlueprintType)
struct FActionMontages : public FTableRowBase
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
    TArray<TObjectPtr<UAnimMontage>> Montages;
         
};