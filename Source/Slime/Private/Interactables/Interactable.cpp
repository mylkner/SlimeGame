// Fill out your copyright notice in the Description page of Project Settings.


#include "Slime/Public/Interactables/Interactable.h"

#include "Components/SphereComponent.h"
#include "Slime/Public/Characters/SlimeCharacter.h"


AInteractable::AInteractable()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	ContactSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ContactSphere->SetupAttachment(RootComponent);
	ContactSphere->SetSphereRadius(ContactSphereRadius);
	ContactSphere->SetCollisionProfileName("OverlapAllDynamic");
}

void AInteractable::BeginPlay()
{
	Super::BeginPlay();

	ContactSphere->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnSphereOverlap);
}


void AInteractable::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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

