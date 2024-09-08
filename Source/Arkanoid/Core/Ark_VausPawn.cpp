// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Ark_VausPawn.h"

// UE:
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
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
	PlayerInputComponent->BindAxis("MoveVaus", this, &AArk_VausPawn::MoveVaus);
}

void AArk_VausPawn::MoveVaus(const float iValue)
{
	if (iValue != 0.f && abs(iValue) <= 1.f)
	{
		VausMesh->AddWorldOffset(FVector::YAxisVector * iValue * MoveCoeff, true);
	}
}

void AArk_VausPawn::AddMoveCoeff()
{
	MoveCoeff *= 1.1f;
}

void AArk_VausPawn::DecMoveCoeff()
{
	MoveCoeff /= 1.1f;
}
//--------------------------------------------------------------------------------------
