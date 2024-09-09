// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Generated:
#include "Ball.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

// UE:
class UProjectileMovementComponent;
//--------------------------------------------------------------------------------------



UCLASS()
class ARKANOID_API ABall : public AActor
{
	GENERATED_BODY()

public:

	/* ---   Constructors   --- */

	// Sets default values for this actor's properties
	ABall();
	//-------------------------------------------



	/* ---   Components   --- */

	/** Меш визуализации мяча */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BallMesh = nullptr;

	/** Компонент передвижения мяча */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	//-------------------------------------------



public:

	/* ---   Velocity   --- */

	// Начальная (стартовая) скорость
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Velocity")
	float StartingVelocity = 500.f;
	//--------------------------------------------------------------------------------------



	/* ---   Collision   --- */

	/**	Событие, когда этот субъект соприкасается с другим */
	virtual void NotifyHit(
		class UPrimitiveComponent* MyComp,
		AActor* Other,
		class UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit) override;

	/**	Событие, когда этот субъект перекрывается с другим */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	//--------------------------------------------------------------------------------------



	/* ---   Gift   --- */

	/** Установка нового значения скорости мяча */
	UFUNCTION(BlueprintCallable, Category = "Gift")
	void SetVelocity(const float NewValue = 1.f);

	/** Добавление скорости мяча */
	UFUNCTION(BlueprintCallable, Category = "Gift")
	void AddVelocity(const float AddValue = 0.1f);
	//-------------------------------------------
};
