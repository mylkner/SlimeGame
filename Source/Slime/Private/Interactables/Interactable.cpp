// Fill out your copyright notice in the Description page of Project Settings.


#include "Slime/Public/Interactables/Interactable.h"

#include "Components/BoxComponent.h"
#include "Slime/Public/Characters/SlimeCharacter.h"


AInteractable::AInteractable()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	ContactBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	ContactBox->SetupAttachment(RootComponent);
	ContactBox->SetBoxExtent(FVector(20.0f, 20.0f, 20.0f));
	ContactBox->SetCollisionProfileName("OverlapAllDynamic");
}

void AInteractable::BeginPlay()
{
	Super::BeginPlay();

	ContactBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnBoxOverlap);
}

void AInteractable::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
									UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASlimeCharacter* Slime = Cast<ASlimeCharacter>(OtherActor))
	{
		Interact(Slime);
	}
}

void AInteractable::Interact(ASlimeCharacter* Slime)
{
	UE_LOG(LogTemp, Warning, TEXT("%s: Interact not implemented!!"), *GetName())
}

