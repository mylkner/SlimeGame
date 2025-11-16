// Fill out your copyright notice in the Description page of Project Settings.


#include "Slime/Public/Characters/SlimeCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interactables/Buffs/BuffStruct.h"

ASlimeCharacter::ASlimeCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = SpringArmLength;
	SpringArm->bUsePawnControlRotation = true;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	ViewCamera->SetupAttachment(SpringArm);

	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
	GetCharacterMovement()->JumpZVelocity = BaseJumpHeight;
	Scale = BaseSize;
	SetActorScale3D(FVector(Scale, Scale, Scale));
}

void ASlimeCharacter::AddBuff(const FBuffStruct& Buff)
{
	for (FBuffStruct& B : CurrentBuffs)
	{
		if (B.Type == Buff.Type)
		{
			B.TimeRemaining = Buff.Duration;
			return;
		}
	}
	
	switch (Buff.Type)
	{
	case EBuffTypes::Jump: GetCharacterMovement()->JumpZVelocity *= Buff.Multiplier; break;
	case EBuffTypes::Speed: GetCharacterMovement()->MaxWalkSpeed *= Buff.Multiplier; break;
	case EBuffTypes::IncreaseSizeFromBuildings:
		SizeFactor *= Buff.Multiplier;
		break;
	case EBuffTypes::Size:
		SizeMultiplier *= Buff.Multiplier;
		Scale = BaseSize * SizeMultiplier;
		break;
	}
	CurrentBuffs.Add(Buff);
}

void ASlimeCharacter::OnEat(const float SizeIncrease)
{
	BaseSize += SizeIncrease * SizeFactor;
	Scale = BaseSize * SizeMultiplier;
	SpringArmLength = 100 * Scale + 500; // og radius * scale + some number to keep spring arm constant distance from slime surface
}

void ASlimeCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(SlimeMappingContext, 0);
		}
	}
}

void ASlimeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASlimeCharacter::Move);
		EnhancedInputComp->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASlimeCharacter::Look);
		EnhancedInputComp->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASlimeCharacter::Jump);
	}
}

void ASlimeCharacter::Tick(const float DeltaTime)
{
	if (SpringArm->TargetArmLength != SpringArmLength)
	{
		SpringArm->TargetArmLength = FMath::FInterpTo(
			SpringArm->TargetArmLength,
			SpringArmLength,
			DeltaTime,
			1.0f
			);
	}

	if (GetActorScale() != FVector(Scale, Scale, Scale))
	{
		// can use any x,y,z of actor scale since should be kept uniform
		const float ScaleInterop = FMath::FInterpTo(GetActorScale().X,
			Scale,
			DeltaTime,
			5.f
			);
		SetActorScale3D(FVector(ScaleInterop, ScaleInterop, ScaleInterop));
	}

	for (int i = CurrentBuffs.Num() - 1; i >= 0; i--)
	{
		CurrentBuffs[i].TimeRemaining -= DeltaTime;
		if (CurrentBuffs[i].TimeRemaining <= 0)
			RemoveBuff(CurrentBuffs[i].Type);
	}
}

void ASlimeCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();

	const FRotator YawRotator = FRotator(0, Controller->GetControlRotation().Yaw, 0);
	const FVector Forward = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(Forward, MoveVector.Y);
	AddMovementInput(Right, MoveVector.X);
}

void ASlimeCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void ASlimeCharacter::RemoveBuff(const EBuffTypes BuffType)
{
	for (int i = CurrentBuffs.Num() - 1; i >= 0; i--)
	{
		if (CurrentBuffs[i].Type == BuffType)
		{
			switch (BuffType)
			{
			case EBuffTypes::Jump: GetCharacterMovement()->JumpZVelocity /= CurrentBuffs[i].Multiplier; break;
			case EBuffTypes::Speed: GetCharacterMovement()->MaxWalkSpeed /= CurrentBuffs[i].Multiplier; break;
			case EBuffTypes::Size: 
				SizeMultiplier /= CurrentBuffs[i].Multiplier;
				Scale = BaseSize;
				break;
			case EBuffTypes::IncreaseSizeFromBuildings:
				SizeFactor /= CurrentBuffs[i].Multiplier;
				break;
			}
			CurrentBuffs.RemoveAt(i);
		}
	}
}

