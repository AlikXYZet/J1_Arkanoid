// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

// Generated:
#include "Ark_VausPawn.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

class UCameraComponent;
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



protected:



	/* ---   Input   --- */

	/** Позволяет пешке настраивать пользовательские привязки ввода. Вызывается при владении устройством PlayerController с использованием InputComponent, созданного CreatePlayerInputComponent(). */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Смещение каретки вдоль оси Y с учётом коллизии и Коэффициентом перемещения */
	void MoveVaus(const float iValue);
	//-------------------------------------------



public:

	/* ---   Components   --- */

	/** Меш визуализации каретки */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* VausMesh = nullptr;

	/** Камера Игрока */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera = nullptr;
	//-------------------------------------------



	/* ---   Input   --- */

	/** Увеличить Коэффициент перемещения на 10% */
	void AddMoveCoeff();

	/** Уменьшить Коэффициент перемещения на 10% */
	void DecMoveCoeff();
	//-------------------------------------------



private:

	/* ---   Input   --- */

	// Коэффициент перемещения каретки
	float MoveCoeff = 2;
	//-------------------------------------------
};
