// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Ball.h"

// UE:
#include "GameFramework/KillZVolume.h"
#include "GameFramework/ProjectileMovementComponent.h"

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
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->bConstrainToPlane = true;
	ProjectileMovement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);
	ProjectileMovement->InitialSpeed = StartingVelocity;
	//-------------------------------------------
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
}

void ABall::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (Cast<AKillZVolume>(OtherActor))
	{
		Destroy();
	}
}
//--------------------------------------------------------------------------------------



/* ---   Gift   --- */

void ABall::SetVelocity(const float iNewValue)
{
	ProjectileMovement->Velocity = ProjectileMovement->Velocity.GetSafeNormal() * iNewValue;
}

void ABall::AddVelocity(const float iAddValue)
{
	ProjectileMovement->Velocity += ProjectileMovement->Velocity.GetSafeNormal() * iAddValue;
}
//--------------------------------------------------------------------------------------
