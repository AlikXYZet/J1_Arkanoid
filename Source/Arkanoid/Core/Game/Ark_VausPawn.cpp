// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Ark_VausPawn.h"

// UE:
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Interaction:
#include "Ark_GameStateBase.h"
#include "Ark_PlayerController.h"
#include "Arkanoid/Elements/Vaus.h"
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

	VausComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Vaus Component"));
	VausComponent->SetupAttachment(RootComponent);
	VausComponent->SetRelativeLocation(BaseLocation);

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
//--------------------------------------------------------------------------------------



/* ---   Base   --- */

void AArk_VausPawn::BeginPlay()
{
	Super::BeginPlay();

	pVausActor = Cast<AVaus>(VausComponent->GetChildActor());

	if (pVausActor)
	{
		pVausActor->SetPawnPointer(this);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AArk_VausPawn::BeginPlay: pVausActor is NOT"));
	}

	CalculateMoveLimit_Y();

	InitStatisticsSystem();
}
//--------------------------------------------------------------------------------------



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

void AArk_VausPawn::MoveVaus(float iValue)
{
	// Корректировка при суммировании нажатий
	if (iValue)
		iValue = iValue < 0 ? -1.f : 1.f;

	// Текущая позиция на оси Y
	float lCurrent_Y = VausComponent->GetRelativeLocation().Y;

	// Заданное смещение местоположения по оси Y
	float lOffset_Y = iValue * MoveCoeff;

	// Контроль местоположения каретки в заданных пределах
	if (lOffset_Y > CurrentMoveLimit_Y - lCurrent_Y)
	{
		lOffset_Y = CurrentMoveLimit_Y - lCurrent_Y;
	}
	else if (lOffset_Y < -CurrentMoveLimit_Y - lCurrent_Y)
	{
		lOffset_Y = -CurrentMoveLimit_Y - lCurrent_Y;
	}

	if (lOffset_Y)
	{
		VausComponent->AddLocalOffset(FVector(0, lOffset_Y, 0));

		// Контроль спавна мяча в направлении движения
		if (SpawnYaw < 0 && iValue > 0)
		{
			SpawnYaw = abs(SpawnYaw);
		}
		else if (SpawnYaw > 0 && iValue < 0)
		{
			SpawnYaw *= -1;
		}
	}
}

void AArk_VausPawn::BallLaunch()
{
	int32 lNumBalls = CurrentArkGameState->GetNumBufferBalls();

	if (lNumBalls > 0)
	{
		ABall* lBlock = GetWorld()->SpawnActor<ABall>(
			BallType.Get(),
			VausComponent->GetComponentLocation() + FVector(20.f, 0.f, 0.f),
			FRotator(0.f, SpawnYaw, 0.f));

		// Если мяч создан, то уменьшить счётчик
		if (lBlock)
		{
			UpdateBallCountStatistics(lNumBalls - 1);
		}
	}
}
//--------------------------------------------------------------------------------------



/* ---   Move   --- */

void AArk_VausPawn::CalculateMoveLimit_Y()
{
	if (pVausActor)
	{
		FVector lOrigin;
		FVector lExtent;
		pVausActor->GetActorBounds(false, lOrigin, lExtent);

		CurrentMoveLimit_Y = MoveLimit_Y - lExtent.Y;

		// Поправить местоположение каретки
		MoveVaus(0);
		// PS: Исправляет баг выхода каретки за пределы,
		// при увеличении её ширины и её местоположении около края Расчётного лимита
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AArk_VausPawn::CalculateMoveLimit_Y: pVausActor is NOT"));
	}
}
//--------------------------------------------------------------------------------------



/* ---   Gift   --- */

void AArk_VausPawn::SetMoveCoeff(float iNewValue)
{
	if (iNewValue < MinMoveCoeff)
	{
		iNewValue = MinMoveCoeff;
	}

	MoveCoeff = iNewValue;
}

void AArk_VausPawn::AddMoveCoeff(const float iAddValue)
{
	if (MoveCoeff != MinMoveCoeff || iAddValue > 0)
	{
		if (MoveCoeff + iAddValue < MinMoveCoeff)
		{
			MoveCoeff = MinMoveCoeff;
		}
		else
		{
			MoveCoeff += iAddValue;
		}
	}
}

void AArk_VausPawn::AddBalls(const int32 iAddValue)
{
	if (CurrentArkGameState)
	{
		int32 lNumBalls = CurrentArkGameState->GetNumBufferBalls();

		if (lNumBalls + iAddValue <= 0)
		{
			lNumBalls = 0;
		}
		else
		{
			lNumBalls += iAddValue;
		}

		UpdateBallCountStatistics(lNumBalls);
	}
}

void AArk_VausPawn::AddWidth(const float iAddValue)
{
	if (pVausActor)
	{
		pVausActor->AddWidth(iAddValue);

		CalculateMoveLimit_Y();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AArk_VausPawn::AddWidth: pVausActor is NOT"));
	}
}

void AArk_VausPawn::SetBallsModeForTime(const float iTime, const EBallMode iMode)
{
	ModifiedBalls = GetAllBalls();

	for (ABall* lBall : ModifiedBalls)
	{
		if (lBall)
		{
			lBall->SetMode(iMode);
		}
	}

	GetWorldTimerManager().SetTimer(Timer_BallsMode, this, &AArk_VausPawn::ResetBallsModeForTime, iTime, false);
}

TArray<ABall*> AArk_VausPawn::GetAllBalls()
{
	TArray<ABall*> lResult;
	TArray<AActor*> lResultActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABall::StaticClass(), lResultActors);

	for (AActor* Data : lResultActors)
	{
		lResult.Add(Cast<ABall>(Data));
	}

	return lResult;
}

void AArk_VausPawn::ResetBallsModeForTime()
{
	for (ABall* lBall : ModifiedBalls)
	{
		if (lBall)
		{
			lBall->SetMode(EBallMode::Base);
		}
	}
}
//--------------------------------------------------------------------------------------



/* ---   Statistics   --- */

void AArk_VausPawn::ResetDefaultTransform()
{
	VausComponent->SetRelativeLocation(BaseLocation);

	if (pVausActor)
	{
		pVausActor->ResetWidth();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AArk_VausPawn::ResetDefaultTransform: pVausActor is NOT"));
	}
}

void AArk_VausPawn::InitStatisticsSystem()
{
	CurrentArkGameState = GetWorld()->GetGameState<AArk_GameStateBase>();

	if (CurrentArkGameState)
	{
		CurrentArkGameState->SetVausPawn(this);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AArk_VausPawn::Init: CurrentArkGameState is NOT"));
	}

	BaseLocation = VausComponent->GetRelativeLocation();
}

void AArk_VausPawn::UpdateBallCountStatistics(const int32& iNumber)
{
	if (CurrentArkGameState)
	{
		CurrentArkGameState->SetBufferBallCounter(iNumber);
	}
}
//--------------------------------------------------------------------------------------
