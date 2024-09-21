// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Vaus.h"

// UE:
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"

// Plugins:
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

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
	//-------------------------------------------



	/* ---   Components: Left   --- */

	LeftRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Left Root"));
	LeftRoot->SetupAttachment(RootComponent);
	LeftRoot->SetRelativeLocation(FVector(0.f, -50.f, 0.f));

	LeftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Mesh"));
	LeftMesh->SetupAttachment(LeftRoot);
	LeftMesh->SetCastShadow(false);
	LeftMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.4f));
	LeftMesh->SetCollisionProfileName(TEXT("Pawn"));

	ArrowLeftFX = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Left FX"));
	ArrowLeftFX->SetupAttachment(LeftRoot);
	ArrowLeftFX->SetRelativeTransform(FTransform(
		FRotator(0.f, -90.f, 0.f),
		FVector(0.f, -5.f, 0.f),
		FVector(0.1f)));
	//-------------------------------------------



	/* ---   Components: Right   --- */

	RightRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Right Root"));
	RightRoot->SetupAttachment(RootComponent);
	RightRoot->SetRelativeLocation(FVector(0.f, 50.f, 0.f));

	RightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Mesh"));
	RightMesh->SetupAttachment(RightRoot);
	RightMesh->SetCastShadow(false);
	RightMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.4f));
	RightMesh->SetCollisionProfileName(TEXT("Pawn"));

	ArrowRightFX = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Right FX"));
	ArrowRightFX->SetupAttachment(RightRoot);
	ArrowRightFX->SetRelativeTransform(FTransform(
		FRotator(0.f, 90.f, 0.f),
		FVector(0.f, 5.f, 0.f),
		FVector(0.1f)));
	//-------------------------------------------
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
		UpdateSecondaryComponentsLocation();
	}
}

void AVaus::ResetWidth()
{
	VausMesh->SetRelativeScale3D(BaseScale3D);

	UpdateSecondaryComponentsLocation();
}

void AVaus::SetPawnPointer(AArk_VausPawn* iVausPawn)
{
	pVausPawn = iVausPawn;
}

AArk_VausPawn* AVaus::GetPawnPointer()
{
	return pVausPawn;
}

void AVaus::UpdateSecondaryComponentsLocation()
{
	// Получение половины размера главного Компонента вдоль оси Y с учётом его масштабирования
	float lExtent_Y = VausMesh->CalcBounds(VausMesh->GetComponentTransform()).BoxExtent.Y;

	// Перемещение вторичных Компонентов (Мешей) на края главного Компонента
	LeftRoot->SetRelativeLocation(FVector(0.f, -lExtent_Y, 0.f));
	RightRoot->SetRelativeLocation(FVector(0.f, lExtent_Y, 0.f));
}
//--------------------------------------------------------------------------------------



/* ---   Move Reaction   --- */

void AVaus::MoveReaction(const float& iDirection)
{
	if (iDirection)
	{
		if (iDirection > 0)
		{
			if (LeftFX)
			{
				UGameplayStatics::SpawnEmitterAtLocation(
					GetWorld(),
					LeftFX,
					ArrowLeftFX->GetComponentTransform());
			}

			if (LeftNiagaraFX)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(
					GetWorld(),
					LeftNiagaraFX,
					ArrowLeftFX->GetComponentLocation(),
					ArrowLeftFX->GetComponentRotation() + FRotator(-90, 0, 0),
					ArrowLeftFX->GetComponentScale());
			}
		}
		else
		{
			if (RightFX)
			{
				UGameplayStatics::SpawnEmitterAtLocation(
					GetWorld(),
					RightFX,
					ArrowRightFX->GetComponentTransform());
			}

			if (RightNiagaraFX)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(
					GetWorld(),
					RightNiagaraFX,
					ArrowRightFX->GetComponentLocation(),
					ArrowRightFX->GetComponentRotation() + FRotator(-90, 0, 0),
					ArrowRightFX->GetComponentScale());
			}
		}
	}
}
//--------------------------------------------------------------------------------------
