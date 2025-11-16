// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SlimeAnim.generated.h"

class UCharacterMovementComponent;
class ASlimeCharacter;
/**
 * 
 */
UCLASS()
class SLIME_API USlimeAnim : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) 	override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ASlimeCharacter> Slime = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Movement")
	TObjectPtr<UCharacterMovementComponent> SlimeMovement = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Movement")
	float GroundSpeed = 0.f;
	
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	bool bIsFalling = false;
};
