// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Ball.h"

// UE:
#include "GameFramework/KillZVolume.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Plugins:
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Interaction:
#include "Block.h"
#include "Arkanoid/Core/Game/Ark_GameStateBase.h"
//--------------------------------------------------------------------------------------



/* ---   Constructors   --- */

// Sets default values
ABall::ABall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Предварительно



	/* ---   Actor   --- */

	// Параметр спавна: Не создавать, если что-то мешает
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	//-------------------------------------------



	/* ---   Components   --- */

	// Корневой компонент
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	RootComponent = BallMesh;
	BallMesh->SetRelativeScale3D(FVector(0.2f));
	BallMesh->SetCastShadow(false);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	// Настройки отскока (идеально упругий мяч):
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1.f;
	ProjectileMovement->Friction = 0.f;
	// Ограничения движения по плостости (без изменения по Z-оси):
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->bConstrainToPlane = true;
	ProjectileMovement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);
	// Задать начальную скорость
	ProjectileMovement->InitialSpeed = StartingVelocity;

	// FX
	FXComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FX"));
	FXComponent->SetupAttachment(RootComponent);

	// FX Niagara
	NiagaraFXComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FX Niagara"));
	NiagaraFXComponent->SetupAttachment(RootComponent);
	//-------------------------------------------
}



/* ---   Base   --- */

void ABall::BeginPlay()
{
	Super::BeginPlay();

	InitFXComponent();

	RememberBaseVisual();
}
//--------------------------------------------------------------------------------------



/* ---   Collision   --- */

void ABall::NotifyHit(
	UPrimitiveComponent* MyComp,
	AActor* Other,
	UPrimitiveComponent* OtherComp,
	bool bSelfMoved,
	FVector HitLocation,
	FVector HitNormal,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	Super::NotifyHit(
		MyComp,
		Other,
		OtherComp,
		bSelfMoved,
		HitLocation,
		HitNormal,
		NormalImpulse,
		Hit);

	if (ABlock* lHitBlock = Cast<ABlock>(Other))
	{
		lHitBlock->ReductionLives();
	}
	else
	{
		// Проверка и выход Мяча из "вечного" отскока от стен границ
		if (FMath::IsNearlyEqual(abs(ProjectileMovement->Velocity.X), 0.f, 5.f))
		{
			++BadHitCounter;

			if (BadHitCounter > 3)
			{
				BadHitCounter = 0;
				ProjectileMovement->Velocity.X -= 10.f;
			}
		}
	}



	/* ---   Collision: FX   --- */

	if (HitFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitFX,
			Hit.ImpactPoint,
			Hit.ImpactNormal.Rotation() + RotationCorrectionForHitFX,
			Scale3DForHitFX);
	}

	if (HitNiagaraFX)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			HitNiagaraFX,
			Hit.ImpactPoint,
			Hit.ImpactNormal.Rotation() + RotationCorrectionForHitFX,
			Scale3DForHitFX);
	}
	//-------------------------------------------
}

void ABall::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (Cast<AKillZVolume>(OtherActor))
	{
		Destroy();
	}

	if (CurrentMode == EBallMode::Fire)
	{
		if (ABlock* lHitBlock = Cast<ABlock>(OtherActor))
		{
			lHitBlock->Destroy();
		}
	}
}

void ABall::Destroyed()
{
	if (AArk_GameStateBase* lGameState = GetWorld()->GetGameState<AArk_GameStateBase>())
	{
		lGameState->CheckAllBallsCounter();
	}

	Super::Destroyed();
}
//--------------------------------------------------------------------------------------



/* ---   Gift   --- */

void ABall::SetVelocity(float iNewValue)
{
	if (iNewValue < MinVelocity)
	{
		iNewValue = MinVelocity;
	}

	ProjectileMovement->Velocity = ProjectileMovement->Velocity.GetSafeNormal() * iNewValue;
}

void ABall::AddVelocity(float iAddValue)
{
	FVector lDirection;
	float lLenght;

	ProjectileMovement->Velocity.ToDirectionAndLength(lDirection, lLenght);

	if (lLenght != MinVelocity || iAddValue > 0)
	{
		lLenght += iAddValue;

		if (lLenght < MinVelocity)
		{
			lLenght = MinVelocity;
		}

		ProjectileMovement->Velocity = lDirection * lLenght;
	}
}
//--------------------------------------------------------------------------------------



/* ---   Ball Mode: Materials and FX   --- */

void ABall::InitFXComponent()
{
	// Флаг уничтожения компонента
	bool bDestroy = true;

	// FX
	for (UParticleSystem* Data : ModeFX)
	{
		if (Data)
		{
			bDestroy = false;
		}
	}

	if (bDestroy)
	{
		FXComponent->DestroyComponent();
	}
	//-------------------------------------------

	// Сброс флага
	bDestroy = true;

	// FX Niagara
	for (UNiagaraSystem* Data : ModeNiagaraFX)
	{
		if (Data)
		{
			bDestroy = false;
		}
	}

	if (bDestroy)
	{
		NiagaraFXComponent->DestroyComponent();
	}
	//-------------------------------------------
}

void ABall::SetMode(EBallMode iMode)
{
	CurrentMode = iMode;

	// Collision:
	switch (CurrentMode)
	{
	case EBallMode::Ghost:
		SetCollisionResponseToWorldDynamic(ECollisionResponse::ECR_Ignore);
		break;

	case EBallMode::Fire:
		SetCollisionResponseToWorldDynamic(ECollisionResponse::ECR_Overlap);
		break;

	default:
		SetCollisionResponseToWorldDynamic(ECollisionResponse::ECR_Block);
		break;
	}

	// Visual:
	if (CurrentMode == EBallMode::Base)
	{
		BallMesh->SetMaterial(0, BaseMaterials);
		FXComponent->SetTemplate(BaseParticle);
		NiagaraFXComponent->SetAsset(BaseNiagara);
	}
	else
	{
		BallMesh->SetMaterial(0, ModeMaterials[uint8(CurrentMode)]);
		FXComponent->SetTemplate(ModeFX[uint8(CurrentMode)]);
		NiagaraFXComponent->SetAsset(ModeNiagaraFX[uint8(CurrentMode)]);
	}
}

void ABall::SetCollisionResponseToWorldDynamic(ECollisionResponse iECR)
{
	BallMesh->SetCollisionResponseToChannel(
		ECollisionChannel::ECC_WorldDynamic,
		iECR);
}

void ABall::RememberBaseVisual()
{
	BaseMaterials = BallMesh->GetMaterial(0);
	BaseParticle = FXComponent->Template;
	BaseNiagara = NiagaraFXComponent->GetAsset();
}
//--------------------------------------------------------------------------------------
