#pragma once

#include "CoreMinimal.h"
#include "AISenseState.generated.h"

UENUM(BlueprintType)
enum class EAISenseState : uint8
{
	None = 0,
	Sight,
	Hearing,
	Damaging
};