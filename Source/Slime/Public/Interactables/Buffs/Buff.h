// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slime/Public/Interactables/Interactable.h"
#include "Buff.generated.h"

UCLASS()
class SLIME_API ABuff : public AInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuff();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
