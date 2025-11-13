// Fill out your copyright notice in the Description page of Project Settings.


#include "Slime/Public/Interactables/Buffs/Buff.h"
#include "Interactables/Buffs/BuffStruct.h"
#include "Slime/Public/Characters/SlimeCharacter.h"

ABuff::ABuff()
{
	BuffType = EBuffTypes::Speed;
}

void ABuff::BeginPlay()
{
	Super::BeginPlay();
}

void ABuff::Interact(ASlimeCharacter* Slime)
{
	UE_LOG(LogTemp, Warning, TEXT("I'm a buff"));

	FBuffStruct Buff;
	Buff.Type = BuffType;
	Buff.Multiplier = Multiplier;
	Buff.Duration = Duration;
	Buff.TimeRemaining = Duration;

	Slime->AddBuff(Buff);
	Remove();
}

void ABuff::Remove()
{
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	Add(FVector(0, 0, 0));
}

void ABuff::Add(const FVector& NewLocation )
{
	SetActorLocation(NewLocation);
	//SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
}





