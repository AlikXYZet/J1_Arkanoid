// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Ball.h"

// UE:
#include "GameFramework/KillZVolume.h"

// Interaction:
#include "Block.h"
//--------------------------------------------------------------------------------------



/* ---   Constructors   --- */

// Sets default values
ABall::ABall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Предварительно



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
	ProjectileMovement->bConstrainToPlane = true;
	ProjectileMovement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);
	//-------------------------------------------



	/* ---   Предварительные значения   --- */

	SetVelocity(500.f);
	//-------------------------------------------
}
//--------------------------------------------------------------------------------------



/* ---   Base   --- */

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	BallMesh->OnComponentHit.AddDynamic(this, &ABall::OnBlockHit);
}
//--------------------------------------------------------------------------------------



/* ---   Velocity   --- */

void ABall::SetVelocity(const float& iNewVelocity)
{
	ProjectileMovement->InitialSpeed = iNewVelocity;
}
//--------------------------------------------------------------------------------------



/* ---   Hit   --- */

void ABall::OnBlockHit(
	UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	if (Cast<AKillZVolume>(OtherActor))
	{
		Destroy();
	}
	else
	{
		GetVelocity();

		if (ABlock* lHitBlock = Cast<ABlock>(OtherActor))
		{
			lHitBlock->SetBlockMaterial();
		}
	}

	// PS: Возможно потребуется заменить "Cast" на группирование объектов по коллизии
}
//--------------------------------------------------------------------------------------
