// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Ark_VausPawn.h"

// UE:
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"

// Interaction:
#include "Arkanoid/Elements/Ball.h"
//--------------------------------------------------------------------------------------



/* ---   Constructors   --- */

// Sets default values
AArk_VausPawn::AArk_VausPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Предварительно



	/* ---   Components   --- */

	// Корневой компонент
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	VausMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Vaus Mesh"));
	VausMesh->SetupAttachment(RootComponent);
	VausMesh->SetRelativeLocation(FVector(-460.f, 0.f, 45.f));
	VausMesh->SetRelativeScale3D(FVector(0.1f, 1.f, 0.4f));
	VausMesh->SetCastShadow(false);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(-370.f, 0.f, 810.f));
	Camera->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));
	//-------------------------------------------



	/* ---   Предварительные значения   --- */

	// Автоподхват игрока
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// Warning: Данный способ дважды ввызывает PossessedBy(*)
	//-------------------------------------------
}



/* ---   Input   --- */

void AArk_VausPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);


	/* ---   Action   --- */

	PlayerInputComponent->BindAction("BallLaunch", EInputEvent::IE_Released, this, &AArk_VausPawn::BallLaunch);
	//-------------------------------------------


	/* ---   Axis   --- */

	PlayerInputComponent->BindAxis("MoveVaus", this, &AArk_VausPawn::MoveVaus);
	//-------------------------------------------
}

void AArk_VausPawn::MoveVaus(const float iValue)
{
	if (iValue != 0.f && abs(iValue) <= 1.f)
	{
		VausMesh->AddWorldOffset(FVector::YAxisVector * iValue * MoveCoeff, true);

		// Контроль спавна мяча в направлении движения
		if (SpawnYaw > 0 && iValue > 0)
		{
			SpawnYaw = abs(SpawnYaw);
		}
		else if (SpawnYaw < 0 && iValue < 0)
		{
			SpawnYaw *= -1;
		}
	}
}

void AArk_VausPawn::BallLaunch()
{
	if (NumBalls > 0)
	{
		// Параметр спавна: Не создавать, если что-то мешает
		FActorSpawnParameters lSpawnParameters = FActorSpawnParameters();
		lSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		ABall* lBlock = GetWorld()->SpawnActor<ABall>(
			BallType.Get(),
			VausMesh->GetComponentLocation() + FVector(20.f, 0.f, 0.f),
			FRotator(0.f, SpawnYaw, 0.f),
			lSpawnParameters);

		// Если мяч создан, то уменьшить счётчик
		if (lBlock)
		{
			--NumBalls;
		}
	}
}
//--------------------------------------------------------------------------------------



/* ---   Gift   --- */

void AArk_VausPawn::AddMoveCoeff()
{
	MoveCoeff *= 1.1f;
}

void AArk_VausPawn::DecMoveCoeff()
{
	MoveCoeff /= 1.1f;
}

void AArk_VausPawn::AddOneBall()
{
	++NumBalls;
}
//--------------------------------------------------------------------------------------
