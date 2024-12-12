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

// Plugins:
class UNiagaraComponent;
class UNiagaraSystem;
//--------------------------------------------------------------------------------------



// Режимы Мяча
UENUM(BlueprintType)
enum struct EBallMode : uint8
{
	// Эффект призрака (Игнорирует объекты типа WorldDynamic)
	Ghost,
	// Огненный эффект (Уничтожает блоки с одного касания с игнорированием соприкосновения)
	Fire,

	// Базовый без эффектов
	Base	// Всегда в конце
};



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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components,
		meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BallMesh = nullptr;

	/** Компонент передвижения мяча */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components,
		meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	/** Компонент для Particle System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components,
		meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* FXComponent = nullptr;

	/** Компонент для Niagara System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components,
		meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* NiagaraFXComponent = nullptr;
	//-------------------------------------------



protected:

	/* ---   Base   --- */

	/** Переопределяемое собственное событие, определяющее начало игры для этого актера */
	virtual void BeginPlay() override;

	/** Вызывается, когда этот субъект явно уничтожается во время игрового процесса или в редакторе,
	* но не вызывается во время потоковой передачи уровней или завершения игрового процесса
	*/
	virtual void Destroyed() override;
	//-------------------------------------------



public:

	/* ---   Velocity   --- */

	// Начальная (стартовая) скорость
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters|Velocity",
		meta = (ClampMin = "1", UIMin = "1"))
	float StartingVelocity = 500.f;

	// Минимальная скорость
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters|Velocity",
		meta = (ClampMin = "1", UIMin = "1"))
	float MinVelocity = 50.f;
	//-------------------------------------------



	/* ---   Collision   --- */

	// FX столкновения Мяча
	UPROPERTY(EditAnywhere, Category = "Parameters|Hit")
	UParticleSystem* HitFX;

	// NiagaraFX столкновения Мяча
	UPROPERTY(EditAnywhere, Category = "Parameters|Hit")
	UNiagaraSystem* HitNiagaraFX;

	// Корректировка ротации FX
	UPROPERTY(EditAnywhere, Category = "Parameters|Hit",
		meta = (DisplayName = "Rotation Correction"))
	FRotator RotationCorrectionForHitFX = FRotator(-90, 0, 0);

	// Корректировка Масштабирования FX
	UPROPERTY(EditAnywhere, Category = "Parameters|Hit",
		meta = (DisplayName = "Scale 3D"))
	FVector Scale3DForHitFX = FVector(0.1f);

	//

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
	//-------------------------------------------



	/* ---   Gift   --- */

	/** Установка нового значения скорости мяча */
	UFUNCTION(BlueprintCallable, Category = "Gift")
	void SetVelocity(float NewValue = 500.f);

	/** Добавление скорости мяча */
	UFUNCTION(BlueprintCallable, Category = "Gift")
	void AddVelocity(float AddValue = 50.f);
	//-------------------------------------------



	/* ---   Ball Mode: Materials and FX   --- */

	// Материалы режимов мяча
	UPROPERTY(EditAnywhere, Category = "Parameters|Mode")
	UMaterialInterface* ModeMaterials[EBallMode::Base];

	// FX режимов мяча
	UPROPERTY(EditAnywhere, Category = "Parameters|Mode")
	UParticleSystem* ModeFX[EBallMode::Base];

	// NiagaraFX режимов мяча
	UPROPERTY(EditAnywhere, Category = "Parameters|Mode")
	UNiagaraSystem* ModeNiagaraFX[EBallMode::Base];

	//

	/** Установка режима текущего Мяча */
	void SetMode(EBallMode Mode = EBallMode::Base);
	//-------------------------------------------



private:

	/* ---   Gift   --- */

	// Текущий режим Мяча
	EBallMode CurrentMode = EBallMode::Base;

	//

	/** Установка коллизии с WorldDynamic согласно Режиму мяча */
	void SetCollisionResponseToWorldDynamic(ECollisionResponse iECR = ECollisionResponse::ECR_Block);
	//-------------------------------------------



	/* ---   Ball Mode: Materials and FX   --- */

	// Базовый материал, полученный из BallMesh
	UMaterialInterface* BaseMaterials = nullptr;

	// Базовый FX, полученный из FXComponent
	UParticleSystem* BaseParticle = nullptr;

	// Базовый FX Niagara, полученный из NiagaraFXComponent
	UNiagaraSystem* BaseNiagara = nullptr;

	//

	/** Инициализация FX: Убрать неиспользуемые FX-компоненты */
	void InitFXComponent();

	/** Запомнить базовый визуал, установленный в компонентах Мяча */
	void RememberBaseVisual();
	//-------------------------------------------



	/* ---   Juggling   --- */

	// Счётчик плохих Отскоков мяча
	// @note	Отскок мяча вдоль оси Y от стен границ считается плохим
	uint8 BadHitCounter = 0;
	//-------------------------------------------
};
