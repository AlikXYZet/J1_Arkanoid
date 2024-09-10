﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

// Generated:
#include "Ark_VausPawn.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

// UE:
class UCameraComponent;
class USphereComponent;

// Interaction:
class ABall;
//--------------------------------------------------------------------------------------



UCLASS()
class ARKANOID_API AArk_VausPawn : public APawn
{
	GENERATED_BODY()

public:

	/* ---   Constructors   --- */

	// Sets default values for this pawn's properties
	AArk_VausPawn();
	//-------------------------------------------



	/* ---   Components   --- */

	/** Меш визуализации каретки */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* VausMesh = nullptr;

	/** Камера Игрока */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera = nullptr;
	//-------------------------------------------



protected:

	/* ---   Input   --- */

	/** Позволяет пешке настраивать пользовательские привязки ввода. Вызывается при владении устройством PlayerController с использованием InputComponent, созданного CreatePlayerInputComponent(). */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//-------------------------------------------



public:

	/* ---   Vaus State   --- */

	// Тип генерируемого мяча
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	TSubclassOf<ABall> BallType;

	// Начальное количество мячей
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters", meta = (ClampMin = "1", UIMin = "1"))
	int32 NumBalls = 3;

	// Минимальное значение Коэффициента перемещения
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters", meta = (ClampMin = "0.5", UIMin = "0.5"))
	float MinMoveCoeff = 1.f;

	// Минимальная ширина
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters", meta = (ClampMin = "0.1", UIMin = "0.1"))
	float MinWidth = 0.5f;
	//-------------------------------------------



	/* ---   Gift   --- */

	/** Установка нового значения Коэффициента перемещения */
	UFUNCTION(BlueprintCallable, Category = "Gift")
	void SetMoveCoeff(float NewValue = 2.f);

	/** Добавление Коэффициента перемещения */
	UFUNCTION(BlueprintCallable, Category = "Gift")
	void AddMoveCoeff(const float AddValue = 0.2f);

	/** Добавить какое-то количество Мячей в копилку */
	UFUNCTION(BlueprintCallable, Category = "Gift")
	void AddBalls(const int32 AddValue = 1);

	/** Добавление Коэффициента перемещения */
	UFUNCTION(BlueprintCallable, Category = "Gift")
	void AddWidth(const float AddValue = 0.1f);
	//-------------------------------------------



private:

	/* ---   Input   --- */

	// Коэффициент перемещения каретки
	float MoveCoeff = 2;

	// Смещение спавна по Yaw
	float SpawnYaw = 30;

	//

	/** Смещение каретки вдоль оси Y с учётом коллизии и Коэффициентом перемещения */
	void MoveVaus(const float iValue);

	/** Запуск мяча */
	void BallLaunch();
	//-------------------------------------------
};
