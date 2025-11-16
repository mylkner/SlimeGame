// Fill out your copyright notice in the Description page of Project Settings.


#include "Slime/Public/Interactables/Buffs/Buff.h"

#include "Components/BoxComponent.h"
#include "Interactables/Buffs/BuffStruct.h"
#include "Slime/Public/Characters/SlimeCharacter.h"

ABuff::ABuff()
{
	PrimaryActorTick.bCanEverTick = true;
	BuffType = EBuffTypes::Speed;
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ContactBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ABuff::BeginPlay()
{
	Super::BeginPlay();
}

void ABuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;
	AddActorWorldRotation(FRotator(0, 50.f*DeltaTime, 0));
	AddActorWorldOffset(FVector(0, 0, TransformedSin()));
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
	Destroy();
}

float ABuff::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime*PeriodFactor);
}





