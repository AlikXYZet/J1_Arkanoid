// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Gift.h"

// UE:
#include "GameFramework/KillZVolume.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Interaction:
#include "Arkanoid/Core/Game/Ark_VausPawn.h"
#include "Ball.h"
//--------------------------------------------------------------------------------------



/* ---   Constructors   --- */

// Sets default values
AGift::AGift()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Предварительно



	/* ---   Components   --- */

	// Корневой компонент
	GiftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	RootComponent = GiftMesh;
	GiftMesh->SetRelativeScale3D(FVector(0.2f));
	GiftMesh->SetCastShadow(false);
	GiftMesh->SetCollisionProfileName(TEXT("Trigger"));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->InitialSpeed = StartingVelocity;
	ProjectileMovement->Velocity = -FVector::XAxisVector;
	//-------------------------------------------
}
//--------------------------------------------------------------------------------------



/* ---   Collision   --- */

void AGift::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (Cast<AKillZVolume>(OtherActor))
	{
		Destroy();
	}
	else if (AArk_VausPawn* lPawn = Cast<AArk_VausPawn>(OtherActor))
	{
		EventIsTaken(lPawn);

		Destroy();
	}
}
//--------------------------------------------------------------------------------------



/* ---   Reactions   --- */

TArray<ABall*> AGift::GetAllBalls()
{
	TArray<ABall*> lResult;
	TArray<AActor*> lResultActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABall::StaticClass(), lResultActors);
	// TODO: вставьте здесь оператор return

	for (AActor* Data : lResultActors)
	{
		lResult.Add(Cast<ABall>(Data));
	}

	return lResult;
}
//--------------------------------------------------------------------------------------
