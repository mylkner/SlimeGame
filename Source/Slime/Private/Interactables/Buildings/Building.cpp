// Fill out your copyright notice in the Description page of Project Settings.


#include "Slime/Public/Interactables/Buildings/Building.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/SlimeCharacter.h"
#include "Interactables/Buffs/Buff.h"

ABuilding::ABuilding()
{
	MinSizeToEat = 1;
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

	if (FMath::RandRange(0.f, 1.f) <= BuffDropRate)
		DropBuff();
	
	Slime->OnEat(SizeIncrease);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		EatEffect,
		GetActorLocation() + FVector(0, 0, 50),
		GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), EatSound, GetActorLocation());
	Destroy();
}

void ABuilding::DropBuff()
{
	const TSubclassOf<ABuff> ChosenBuff = Buffs[FMath::RandRange(0, Buffs.Num() - 1)];
	
	GetWorld()->SpawnActor<ABuff>(
		ChosenBuff,
		GetActorLocation() + FVector(FMath::RandRange(0, 1000), FMath::RandRange(0, 1000), 100),
		FRotator::ZeroRotator);
}


