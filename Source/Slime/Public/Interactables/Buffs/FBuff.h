#pragma once

#include "BuffTypes.h"

USTRUCT()
struct FBuff
{
	EBuffTypes Type;
	float Multiplier;
	float Duration;
	float TimeRemaining;
};
