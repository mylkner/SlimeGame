// Fill out your copyright notice in the Description page of Project Settings.


#include "Slime/Public/Interactables/Buffs/Buff.h"

#include "Components/SphereComponent.h"
#include "Slime/Public/Characters/SlimeCharacter.h"

ABuff::ABuff()
{
}

void ABuff::BeginPlay()
{
	Super::BeginPlay();
}

void ABuff::Interact(ASlimeCharacter* Slime)
{
	UE_LOG(LogTemp, Warning, TEXT("I'm a buff"));
}





