// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Generated:
#include "Gift.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

// UE:
class UProjectileMovementComponent;
class UParticleSystemComponent;

// Plugins:
class UNiagaraComponent;

// Interaction:
class AArk_VausPawn;
class ABall;
//--------------------------------------------------------------------------------------



UCLASS()
class ARKANOID_API AGift : public AActor
{
	GENERATED_BODY()

public:

	/* ---   Constructors   --- */

	// Sets default values for this actor's properties
	AGift();
	//-------------------------------------------



	/* ---   Components   --- */

	/** Меш визуализации Подарка */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GiftMesh = nullptr;

	/** Компонент передвижения Подарка */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	/** Компонент для Particle System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* FXComponent = nullptr;

	/** Компонент для Niagara System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* NiagaraFXComponent = nullptr;
	//-------------------------------------------



protected:

	/* ---   Base   --- */

	/** Переопределяемое собственное событие, определяющее начало игры для этого актера */
	virtual void BeginPlay() override;
	//-------------------------------------------



public:

	/* ---   Velocity   --- */

	// Начальная (стартовая) скорость
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	float StartingVelocity = 100.f;
	//-------------------------------------------



	/* ---   Collision   --- */

	/**	Событие, когда этот субъект перекрывается с другим */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	//-------------------------------------------



	/* ---   Reactions   --- */

	/**	Реакция на подбор Пешкой */
	UFUNCTION(BlueprintImplementableEvent, Category = "Reactions", meta = (DisplayName = "Is Taken"))
	void EventIsTaken(AArk_VausPawn* VausPawn);
	//-------------------------------------------



private:

	/* ---   FX   --- */

	/** Инициализация FX: Убрать неиспользуемые FX-компоненты */
	void InitFXComponent();
	//-------------------------------------------
};
