#pragma once

#include "CoreMinimal.h"
#include "EnemyMovementMode.generated.h"

UENUM(BlueprintType)
enum class EEnemyMovementMode : uint8
{
    Idle = 0,
    Walk,
    Jogging, 
    Run
};