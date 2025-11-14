// Fill out your copyright notice in the Description page of Project Settings.


#include "Slime/Public/Interactables/Buffs/Buff.h"

#include "Components/SphereComponent.h"
#include "Interactables/Buffs/BuffStruct.h"
#include "Slime/Public/Characters/SlimeCharacter.h"

ABuff::ABuff()
{
	BuffType = EBuffTypes::Speed;
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ContactSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ABuff::BeginPlay()
{
	Super::BeginPlay();
}

void ABuff::Interact(ASlimeCharacter* Slime)
{
	if (bUsed) return;
	bUsed = true;
	
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
}

void ABuff::Add(const FVector& NewLocation )
{
	SetActorLocation(NewLocation);
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
}





