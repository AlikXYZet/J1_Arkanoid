// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Generated:
#include "Vaus.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

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

	/** Меш визуализации каретки */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftMesh = nullptr;

	/** Меш визуализации каретки */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightMesh = nullptr;
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



private:

	/* ---   Gift   --- */

	// Базовая локация, полученный из VausMesh
	FVector BaseScale3D = FVector(0.1f, 1.f, 0.4f);

	// Указатель на пешку, которому принадлежит
	AArk_VausPawn* pVausPawn;

	//

	void UpdateSecondaryMeshLocation();
	//-------------------------------------------
};
