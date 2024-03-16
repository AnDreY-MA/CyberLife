#pragma once

#include "CoreMinimal.h"
#include "AIState.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Passive = 0,
	Attacking,
	Frozen,
	Investigating,
	Dead
};