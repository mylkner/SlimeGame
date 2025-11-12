// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Edible.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UEdible : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SLIME_API IEdible
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Edible")
	void OnEaten();
};
