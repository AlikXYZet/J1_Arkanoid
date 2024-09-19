// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Vaus.h"

// Interaction:
#include "Arkanoid/Core/Game/Ark_VausPawn.h"
//--------------------------------------------------------------------------------------



/* ---   Constructors   --- */

// Sets default values
AVaus::AVaus()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Предварительно



	/* ---   Components   --- */

	// Корневой компонент
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	VausMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Vaus Mesh"));
	VausMesh->SetupAttachment(RootComponent);
	VausMesh->SetCastShadow(false);
	VausMesh->SetRelativeScale3D(BaseScale3D);
	VausMesh->SetCollisionProfileName(TEXT("Pawn"));

	LeftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Mesh"));
	LeftMesh->SetupAttachment(RootComponent);
	LeftMesh->SetCastShadow(false);
	LeftMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.4f));
	LeftMesh->SetCollisionProfileName(TEXT("Pawn"));

	RightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Mesh"));
	RightMesh->SetupAttachment(RootComponent);
	RightMesh->SetCastShadow(false);
	RightMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.4f));
	RightMesh->SetCollisionProfileName(TEXT("Pawn"));
	//-------------------------------------------

	LeftMesh->SetRelativeLocation(FVector(0.f, -50.f, 0.f));
	RightMesh->SetRelativeLocation(FVector(0.f, 50.f, 0.f));
}
//--------------------------------------------------------------------------------------



/* ---   Base   --- */

void AVaus::BeginPlay()
{
	Super::BeginPlay();

	BaseScale3D = VausMesh->GetRelativeScale3D();
}
//--------------------------------------------------------------------------------------



/* ---   Gift   --- */

void AVaus::AddWidth(const float iAddValue)
{
	FVector lScale = VausMesh->GetRelativeScale3D();

	if (lScale.Y != MinWidth || iAddValue > 0)
	{
		if (lScale.Y + iAddValue < MinWidth)
		{
			lScale.Y = MinWidth;
		}
		else
		{
			lScale.Y += iAddValue;
		}

		VausMesh->SetRelativeScale3D(lScale);
		UpdateSecondaryMeshLocation();
	}
}

void AVaus::ResetWidth()
{
	VausMesh->SetRelativeScale3D(BaseScale3D);

	UpdateSecondaryMeshLocation();
}

void AVaus::SetPawnPointer(AArk_VausPawn* iVausPawn)
{
	pVausPawn = iVausPawn;
}

AArk_VausPawn* AVaus::GetPawnPointer()
{
	return pVausPawn;
}

void AVaus::UpdateSecondaryMeshLocation()
{
	// Получение половины размера главного Компонента вдоль оси Y с учётом его масштабирования
	float lExtent_Y = VausMesh->CalcBounds(VausMesh->GetComponentTransform()).BoxExtent.Y;

	// Перемещение вторичных Компонентов на края главного Компонента
	LeftMesh->SetRelativeLocation(FVector(0.f, -lExtent_Y, 0.f));
	RightMesh->SetRelativeLocation(FVector(0.f, lExtent_Y, 0.f));
}
//--------------------------------------------------------------------------------------
