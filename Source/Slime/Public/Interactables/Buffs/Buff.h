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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buffs")
	EBuffTypes BuffType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buffs")
	float Multiplier = 1.1f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buffs")
	float Duration = 15.0f;

private:
	// remove/add from game
	UFUNCTION()
	void Remove();

	UFUNCTION()
	void Add(const FVector& NewLocation);

	// stop dupes
	bool bUsed = false;
};
