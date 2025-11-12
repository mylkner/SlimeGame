// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffTypes.h"
#include "Slime/Public/Interactables/Interactable.h"
#include "Buff.generated.h"

UCLASS()
class SLIME_API ABuff : public AInteractable
{
	GENERATED_BODY()

public:
	ABuff();

protected:
	virtual void BeginPlay() override;
	virtual void Interact(ASlimeCharacter* Slime) override;

	// properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs")
	EBuffTypes BuffType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs")
	float Multiplier = 1.1f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs")
	float Time = 15.0f;
};
