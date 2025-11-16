// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

class ASlimeCharacter;
class UBoxComponent;

UCLASS(Abstract)
class SLIME_API AInteractable : public AActor
{
	GENERATED_BODY() 

public:
	explicit AInteractable();
	
protected:
	virtual void BeginPlay() override;
	
	// overlap
	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// event
	UFUNCTION(BlueprintCallable, Category="Interactable")
	virtual void Interact(ASlimeCharacter* Slime);
	
	// components
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> ContactBox;
};
