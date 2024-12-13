// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

// Interaction:
#include "Arkanoid/Elements/Ball.h"

// Generated:
#include "Ark_VausPawn.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

// UE:
class UCameraComponent;
class UBoxComponent;

// Interaction:
class AArk_GameStateBase;
class AVaus;
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

	// Актор каретки
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components,
		meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* VausComponent = nullptr;

	// Камера Игрока
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components,
		meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera = nullptr;
	//-------------------------------------------



protected:

	/* ---   Base   --- */

	/** Переопределяемое собственное событие, определяющее начало игры для этого актера */
	void virtual BeginPlay() override;
	//-------------------------------------------



	/* ---   Input   --- */

	/** Позволяет пешке настраивать пользовательские привязки ввода. Вызывается при владении устройством PlayerController с использованием InputComponent, созданного CreatePlayerInputComponent(). */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//-------------------------------------------



public:

	/* ---   Components   --- */

	/** Указатель на Актор каретки */
	AVaus* pVausActor = nullptr;
	//-------------------------------------------



	/* ---   Base   --- */

	/** Функция, вызываемая каждый кадр */
	void virtual Tick(float DeltaSeconds) override;
	//-------------------------------------------



	/* ---   Move   --- */

	// Лимит передвижения каретки по оси Y
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	float MoveLimit_Y = 487.5f;
	//-------------------------------------------



	/* ---   Statistics   --- */

	// Тип генерируемого мяча
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	TSubclassOf<ABall> BallType;

	// Минимальное значение Коэффициента перемещения
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters",
		meta = (ClampMin = "0.5", UIMin = "0.5"))
	float MinMoveCoeff = 1.f;

	//

	/** Сброс трансформации каретки до значений по умолчанию */
	//UFUNCTION(BlueprintCallable, Category = "Parameters")
	void ResetDefaultTransform();
	//-------------------------------------------



	/* ---   Gift   --- */

	/** Установка нового значения Коэффициента перемещения */
	UFUNCTION(BlueprintCallable, Category = "Gift")
	void SetMoveCoeff(float NewValue = 2.f);

	/** Добавление Коэффициента перемещения */
	UFUNCTION(BlueprintCallable, Category = "Gift")
	void AddMoveCoeff(const float AddValue = 0.2f);

	/** Добавить какое-то количество Мячей в Буфер */
	UFUNCTION(BlueprintCallable, Category = "Gift")
	void AddBalls(const int32 AddValue = 1);

	/** Добавление Ширины каретки */
	UFUNCTION(BlueprintCallable, Category = "Gift")
	void AddWidth(const float AddValue = 0.1f);

	/** Установить режим в течение установленного времени для всех Мячей на поле */
	UFUNCTION(BlueprintCallable, Category = "Gift")
	void SetBallsModeForTime(const float Time = 10.f, const EBallMode Mode = EBallMode::Base);

	/** Получить указатели на мячи
	@warning	Есть риск получить НЕ ВАЛИДНЫЙ указатель. Проверяйте указатель перед использованием!
	*/
	UFUNCTION(BlueprintCallable, Category = "Gift")
	TArray<ABall*> GetAllBalls();
	//-------------------------------------------



private:

	/* ---   Input   --- */

	// Смещение спавна по Yaw
	float SpawnYaw = 30;

	//

	/** Смещение каретки вдоль оси Y с учётом коллизии и Коэффициентом перемещения */
	//void MoveVaus(float iValue);

	/** Запуск мяча */
	void BallLaunch();

	/** Запуск перемещения каретки вправо */
	void MoveVausToRight();

	/** Прекратить перемещать каретку вправо */
	void NotMoveVausToRight();

	/** Запуск перемещения каретки влево */
	void MoveVausToLeft();

	/** Прекратить перемещать каретку влево */
	void NotMoveVausToLeft();
	//-------------------------------------------



	/* ---   Move   --- */
	
	// Контроль направление перемещения
	int8 DirectionOfMovement = 0;

	// Коэффициент перемещения каретки
	float MoveCoeff = 200;

	// Расчётный лимит передвижения каретки по оси Y, учитывающий её ширину
	float CurrentMoveLimit_Y;

	//

	/** Рассчитать лимит передвижения каретки по оси Y, учитывая её ширину */
	void MoveVausForTick(const float& DeltaSeconds);

	/** Рассчитать лимит передвижения каретки по оси Y, учитывая её ширину */
	void CalculateMoveLimit_Y();
	//-------------------------------------------



	/* ---   Statistics   --- */

	// Указатель на текущий GameStateBase
	AArk_GameStateBase* CurrentArkGameState = nullptr;

	// Базовая локация, полученный из VausMesh
	FVector BaseLocation = FVector(-460.f, 0.f, 25.f);

	//

	/** Инициализация данных Пешки и передача собственного указателя другим объектам */
	void InitStatisticsSystem();

	/** Обновить статус количества мячей */
	void UpdateBallCountStatistics(const int32& iNumber);
	//-------------------------------------------



	/* ---   Gift   --- */

	// Массив "модифицированных" мячей (с режимом != EBallMode::Base)
	TArray<ABall*> ModifiedBalls;

	// Таймер для режима Мячей
	FTimerHandle Timer_BallsMode;

	//

	/** Сброс режима для всех ранее изменённых Мячей на поле
	@note	Устанавливает режим EBallMode::Base
	*/
	void ResetBallsModeForTime();
	//-------------------------------------------
};
