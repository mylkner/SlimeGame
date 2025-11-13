#pragma once

#include "BuffTypes.h"
#include "BuffStruct.generated.h"

USTRUCT()
struct FBuffStruct
{
	GENERATED_BODY()
	
	EBuffTypes Type;
	float Multiplier;
	float Duration;
	float TimeRemaining;
};
