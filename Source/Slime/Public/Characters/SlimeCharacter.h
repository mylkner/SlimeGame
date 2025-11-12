// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlimeCharacter.generated.h"

class USphereComponent;
struct FInputActionValue;
class UInputMappingContext;
class UInputComponent;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;


UCLASS()
class SLIME_API ASlimeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASlimeCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// input handler fns
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	// input actions/context
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> SlimeMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction = nullptr;

private:
	// components
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> ViewCamera = nullptr;

	// stats/multipliers
	UPROPERTY(VisibleAnywhere)
	float Size = 10.0f;

	UPROPERTY(VisibleAnywhere)
	float SpeedMultiplier = 1.0f;

	UPROPERTY(VisibleAnywhere)
	float JumpMultiplier = 1.0f;

	UPROPERTY(VisibleAnywhere)
	float SizeMultiplier = 1.0f;
};
