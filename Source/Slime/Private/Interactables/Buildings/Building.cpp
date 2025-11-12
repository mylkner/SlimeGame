// Fill out your copyright notice in the Description page of Project Settings.


#include "Slime/Public/Interactables/Buildings/Building.h"

#include "Slime/Public/Characters/SlimeCharacter.h"


ABuilding::ABuilding()
{
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
}

void ABuilding::Interact(ASlimeCharacter* Slime)
{
	UE_LOG(LogTemp, Warning, TEXT("I'm a buff"));
}

