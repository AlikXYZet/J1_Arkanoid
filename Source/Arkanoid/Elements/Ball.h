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



// Режимы Мяча
UENUM(BlueprintType)
enum struct EBallMode : uint8
{
	// Базовый без эффектов
	Base = 0,
	// Эффект призрака (Игнорирует объекты типа WorldDynamic)
	Ghost,
	// Огненный эффект (Уничтожает блоки с одного касания с игнорированием соприкосновения)
	Fire,

	// Всегда в конце
	Max	UMETA(DisplayName = "Invalid")
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BallMesh = nullptr;

	/** Компонент передвижения мяча */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	//-------------------------------------------



protected:

	/* ---   Base   --- */

	/** Переопределяемое собственное событие, определяющее начало игры для этого актера */
	virtual void BeginPlay() override;
	//--------------------------------------------------------------------------------------



public:

	/* ---   Velocity   --- */

	// Начальная (стартовая) скорость
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters", meta = (ClampMin = "1", UIMin = "1"))
	float StartingVelocity = 500.f;

	// Минимальная скорость
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters", meta = (ClampMin = "1", UIMin = "1"))
	float MinVelocity = 50.f;

	/* Материалы режимов мяча
	@note	Материал "Base" применяется автоматически
	*/
	UPROPERTY(EditAnywhere, Category = "Parameters")
	UMaterialInterface* ModeMaterials[EBallMode::Max];
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

	/** Вызывается, когда этот субъект явно уничтожается во время игрового процесса или в редакторе, но не вызывается во время потоковой передачи уровней или завершения игрового процесса */
	virtual void Destroyed() override;
	//--------------------------------------------------------------------------------------



	/* ---   Gift   --- */

	/** Установка нового значения скорости мяча */
	UFUNCTION(BlueprintCallable, Category = "Gift")
	void SetVelocity(float NewValue = 500.f);

	/** Добавление скорости мяча */
	UFUNCTION(BlueprintCallable, Category = "Gift")
	void AddVelocity(float AddValue = 50.f);

	/** Установка режима текущего Мяча */
	void SetMode(EBallMode Mode = EBallMode::Base);
	//-------------------------------------------



private:

	/* ---   Gift   --- */

	// Текущий режим Мяча
	EBallMode CurrentMode = EBallMode::Base;

	void SetCollisionResponseForWorldDynamic(ECollisionResponse iECR = ECollisionResponse::ECR_Block);
	//-------------------------------------------
};
