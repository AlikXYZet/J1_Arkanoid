// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Generated:
#include "Vaus.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

// UE:
class UArrowComponent;

// Plugins:
class UNiagaraComponent;
class UNiagaraSystem;

// Interaction:
class AArk_VausPawn;
//--------------------------------------------------------------------------------------



UCLASS()
class ARKANOID_API AVaus : public AActor
{
	GENERATED_BODY()

public:

	/* ---   Constructors   --- */

	// Sets default values for this actor's properties
	AVaus();
	//-------------------------------------------



	/* ---   Components   --- */

	/** Меш визуализации каретки */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* VausMesh = nullptr;
	//-------------------------------------------



	/* ---   Components: Left   --- */

	/** Левый корневой компонент */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Left", meta = (AllowPrivateAccess = "true"))
	USceneComponent* LeftRoot = nullptr;

	/** Меш визуализации каретки */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Left", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftMesh = nullptr;

	/** Вектор с Трансформацией для FX-реакции слева */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Left", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ArrowLeftFX = nullptr;

	/** Компонент слева для Particle System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Left", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* LeftFXComponent = nullptr;

	/** Компонент слева для Niagara System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Left", meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* LeftNiagaraFXComponent = nullptr;
	//-------------------------------------------



	/* ---   Components: Right   --- */

	/** Правый корневой компонент */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Right", meta = (AllowPrivateAccess = "true"))
	USceneComponent* RightRoot = nullptr;

	/** Меш визуализации каретки */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Right", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightMesh = nullptr;

	/** Вектор с Трансформацией для FX-реакции справа */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Right", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ArrowRightFX = nullptr;

	/** Компонент справа для Particle System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Right", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* RightFXComponent = nullptr;

	/** Компонент справа для Niagara System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Right", meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* RightNiagaraFXComponent = nullptr;
	//-------------------------------------------



protected:

	/* ---   Base   --- */

	/** Переопределяемое собственное событие, определяющее начало игры для этого актера */
	void virtual BeginPlay() override;
	//-------------------------------------------



public:

	/* ---   Gift   --- */

	// Минимальная ширина
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters", meta = (ClampMin = "0.1", UIMin = "0.1"))
	float MinWidth = 0.5f;

	//

	/** Добавление Ширины каретки */
	void AddWidth(const float AddValue = 0.1f);

	/** Сброс Ширины каретки */
	void ResetWidth();

	/** Записать указатель на пешку, которому принадлежит */
	void SetPawnPointer(AArk_VausPawn* iVausPawn);

	/** Получить указатель на пешку, которому принадлежит */
	AArk_VausPawn* GetPawnPointer();
	//-------------------------------------------



	/* ---   Move Reaction   --- */

	/** Запуск реакции на перемещение с учётом направления */
	void MoveReaction(const float& iDirection);
	//-------------------------------------------



	/* ---   Move Reaction: Left   --- */

	// FX слева
	UPROPERTY(EditAnywhere, Category = "Parameters|Move Reaction|Left")
	UParticleSystem* LeftFX;

	// NiagaraFX слева
	UPROPERTY(EditAnywhere, Category = "Parameters|Move Reaction|Left")
	UNiagaraSystem* LeftNiagaraFX;

	// Корректировка ротации FX слева
	UPROPERTY(EditAnywhere, Category = "Parameters|Move Reaction|Left", meta = (DisplayName = "Rotation Correction"))
	FRotator RotationCorrectionForLeftFX = FRotator(-90, 0, 0);

	//

	/**	Реакция при движении вправо */
	UFUNCTION(BlueprintImplementableEvent, Category = "Move Reactions", meta = (DisplayName = "To Right"))
	void EventToRight();
	//-------------------------------------------



	/* ---   Move Reaction: Right   --- */

	// FX справа
	UPROPERTY(EditAnywhere, Category = "Parameters|Move Reaction|Right")
	UParticleSystem* RightFX;

	// NiagaraFX справа
	UPROPERTY(EditAnywhere, Category = "Parameters|Move Reaction|Right")
	UNiagaraSystem* RightNiagaraFX;

	// Корректировка ротации FX справа
	UPROPERTY(EditAnywhere, Category = "Parameters|Move Reaction|Right", meta = (DisplayName = "Rotation Correction"))
	FRotator RotationCorrectionForRightFX = FRotator(-90, 0, 0);

	//

	/**	Реакция при движении влево */
	UFUNCTION(BlueprintImplementableEvent, Category = "Move Reactions", meta = (DisplayName = "To Left"))
	void EventToLeft();
	//-------------------------------------------



private:

	/* ---   Gift   --- */

	// Указатель на пешку, которому принадлежит
	AArk_VausPawn* pVausPawn;

	// Базовая локация, полученный из VausMesh
	FVector BaseScale3D = FVector(0.1f, 1.f, 0.4f);

	// Половина размера 
	float BaseExtent_Y;

	//

	void UpdateSecondaryComponentsLocation();
	//-------------------------------------------



	/* ---   FX   --- */

	/** Инициализация FX: Убрать неиспользуемые FX-компоненты */
	void InitFXComponent();
	//-------------------------------------------
};
