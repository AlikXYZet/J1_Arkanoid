﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

// Interaction:
#include "Arkanoid/Tools/Saving/GameData.h"
#include "Arkanoid/Tools/Saving/LevelData.h"

// Generated:
#include "Ark_GameStateBase.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Delegates   --- */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLivesCounter, int32, Lives);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBufferBallCounter, int32, Count);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreCounter, int32, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOver, bool, bIsGameResult);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelWin, bool, bIsGameResult);
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

// UE:
class UDataTable;

// Interaction:
class AArk_PlayerController;
class AArk_VausPawn;
class UArk_GameInstance;
class USavedGameData;
//--------------------------------------------------------------------------------------



UCLASS()
class ARKANOID_API AArk_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

protected:

	/* ---   Delegates   --- */

	/** Делегат изменения Количества жизней */
	UPROPERTY(BlueprintAssignable, Category = "Statistics|Delegates")
	FOnLivesCounter OnLivesCounter;

	/** Делегат изменения Количества мячей в буфере */
	UPROPERTY(BlueprintAssignable, Category = "Statistics|Delegates")
	FOnBufferBallCounter OnBufferBallCounter;

	/** Делегат изменения Количества очков */
	UPROPERTY(BlueprintAssignable, Category = "Statistics|Delegates")
	FOnScoreCounter OnScoreCounter;

	/** Делегат Окончания игры */
	UPROPERTY(BlueprintAssignable, Category = "Statistics|Delegates")
	FOnGameOver OnGameOver;

	/** Делегат Завершения уровня */
	UPROPERTY(BlueprintAssignable, Category = "Statistics|Delegates")
	FOnLevelWin OnLevelWin;
	//-------------------------------------------



	/* ---   Base   --- */

	/** Переопределяемое собственное событие, определяющее начало игры для этого актера */
	void virtual BeginPlay() override;
	//-------------------------------------------



public:

	/* ---   Statistics   --- */

	// Количество жизней
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	int32 CurrentLives = 3;

	// Количество Мячей в буфере (Обновляется Пешкой)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters", meta = (ClampMin = "1", UIMin = "1"))
	int32 BufferBallCounter = 3;

	//

	/**	Сохранить указатель на Каретку */
	void SetVausPawn(AArk_VausPawn* iPawn);

	/**	Изменить количество Мячей */
	void SetBufferBallCounter(const int32& Count);

	/**	Добавить количество Очков */
	void AddScore(const int32& iAddScore);

	/**	Проверить количество всех мячей (на поле и в буфере) */
	void CheckAllBallsCounter();

	/**	Получить количество Жизней */
	UFUNCTION(BlueprintCallable, Category = "Statistics")
	int32& GetCurrentLives();

	/**	Получить текущее количество Очков */
	UFUNCTION(BlueprintCallable, Category = "Statistics")
	int32& GetCurrentScore();

	/**	Получить рекордное количество Очков */
	UFUNCTION(BlueprintCallable, Category = "Statistics")
	int32& GetRecordScore();

	/**	Получить рекордное количество Очков */
	UFUNCTION(BlueprintCallable, Category = "Statistics")
	int32& GetNumBufferBalls();
	//-------------------------------------------



private:

	/* ---   Statistics   --- */

	// Указатель на текущую Каректу для проверки количества мячей в буффере
	AArk_VausPawn* CurrentVausPawn;

	// Количество очков за игру
	int32 CurrentScore = 0;

	// Рекордное количество очков
	int32 RecordScore = 0;

	//

	/** Метод, хранящий действия при Окончании игры */
	void GameOver();

	/** Метод, хранящий действия при Уменьшении количества жизней */
	void DecLives();

	/** Получить количество Мячей на уровне */
	int32 GetNumberBallsOnLevel();
	//-------------------------------------------



	/* ---   Game Instance   --- */

	// Указатель на текущий GameInstance
	UArk_GameInstance* CurrentSavingInstance;

	//

	/** Инициализация данных GameState */
	void Init();
	//-------------------------------------------



	/* ---   Game Saving   --- */

	/**	Сохранение текущих данных игры */
	bool SaveGameData();

	/**	Получение данных игры */
	void UpdateGameData();
	//-------------------------------------------



	/* ---   Level Saving   --- */

	/** Обновить текущие данные Уровня */
	void UpdateLevelData();

	/** Сохранить текущие данные Уровня */
	void SaveLevelData();

	/**	Обнуление данных Уровня */
	void ClearLevelData();
	//-------------------------------------------
};
