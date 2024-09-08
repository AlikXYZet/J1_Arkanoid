// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// UE4:
#include "GameFramework/ProjectileMovementComponent.h"

// Generated:
#include "Ball.generated.h"
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



	/* ---   Base   --- */

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:

	/* ---   Components   --- */

	/** Меш визуализации мяча */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BallMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	//-------------------------------------------



	/* ---   Velocity   --- */

	/** Установка новой скорости мяча
	* @param	iNewVelocity - Новое значение скорости
	*/
	void SetVelocity(const float& iNewVelocity);

	//-------------------------------------------



	/* ---   Hit   --- */

	/**	Событие, когда этот субъект соприкасается с другим */
	UFUNCTION()
	virtual void OnBlockHit(
		class UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);
	//--------------------------------------------------------------------------------------
};
