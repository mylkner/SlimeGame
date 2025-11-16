// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slime/Public/Interactables/Interactable.h"
#include "Building.generated.h"

class ABuff;
class UNiagaraSystem;

UCLASS()
class SLIME_API ABuilding : public AInteractable
{
	GENERATED_BODY()

public:
	ABuilding();

protected:
	virtual void BeginPlay() override;
	virtual void Interact(ASlimeCharacter* Slime) override;

	// props
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buildings")
	float MinSizeToEat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buildings")
	float SizeFactor;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buildings")
	float SizeIncrease;
	
	// effects
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buildings|Effects")
	TObjectPtr<UNiagaraSystem> EatEffect = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buildings|Effects")
	TObjectPtr<USoundBase> EatSound = nullptr;

	// buff drop
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buffs")
	TArray<TSubclassOf<ABuff>> Buffs;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buffs")
	float BuffDropRate = .15f;

	UFUNCTION()
	void DropBuff();
};
