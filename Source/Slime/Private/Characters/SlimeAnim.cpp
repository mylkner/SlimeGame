// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlimeAnim.h"

#include "Characters/SlimeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void USlimeAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Slime = Cast<ASlimeCharacter>(TryGetPawnOwner());
	// if (Slime)
	// {
	// 	SlimeMovement = Slime->GetCharacterMovement();
	// }
}

void USlimeAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Slime || !SlimeMovement) return;
	
	GroundSpeed = SlimeMovement->Velocity.Size2D();
	bIsFalling = SlimeMovement->IsFalling();
}
