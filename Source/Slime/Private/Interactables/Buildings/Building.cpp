// Fill out your copyright notice in the Description page of Project Settings.


#include "Slime/Public/Interactables/Buildings/Building.h"

#include "Characters/SlimeCharacter.h"

ABuilding::ABuilding()
{
	MinSizeToEat = 1.1;
	SizeFactor = 10;
	SizeIncrease = MinSizeToEat / SizeFactor;
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
}

void ABuilding::Interact(ASlimeCharacter* Slime)
{
	if (Slime->GetSize() < MinSizeToEat) return;
	Slime->OnEat(SizeIncrease);
	Destroy();
}

