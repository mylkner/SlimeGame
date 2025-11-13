// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlimeCharacter.generated.h"

enum class EBuffTypes : uint8;
struct FBuffStruct;
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

	UFUNCTION()
	void AddBuff(const FBuffStruct& Buff);

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

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
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> ViewCamera = nullptr;

	// stats/multipliers
	const float BaseSpeed = 700;
	const float BaseJumpHeight = 500;

	UPROPERTY(VisibleAnywhere)
	float SpeedMultiplier = 1.0f;

	UPROPERTY(VisibleAnywhere)
	float JumpMultiplier = 1.0f;

	UPROPERTY(VisibleAnywhere)
	float SizeMultiplier = 1.1f;

	// buffs
	TArray<FBuffStruct> CurrentBuffs = TArray<FBuffStruct>();

	UFUNCTION()
	void RemoveBuff(EBuffTypes BuffType);
};
