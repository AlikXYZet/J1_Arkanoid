// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

// Interaction:
#include "Arkanoid/Tools/Saving/GameData.h"

// Generated:
#include "Ark_GameStateBase.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

// Interaction:
class AArk_PlayerController;
class AArk_VausPawn;
class USavingInstance;
class USavedGameData;
//--------------------------------------------------------------------------------------



UCLASS()
class ARKANOID_API AArk_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

protected:

	/* ---   Base   --- */

	/** Переопределяемое собственное событие, определяющее начало игры для этого актера */
	void virtual BeginPlay() override;
	//-------------------------------------------



public:

	/* ---   Statistics   --- */

	// Количество жизней
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	int32 CurrentLives = 3;

	//

	/**	Сохранить указатель на Каретку */
	void SetVausPawn(AArk_VausPawn* iPawn);

	/**	Изменить количество Мячей */
	void SetBufferBallCounter(const int32& Count);

	/**	Event изменения количества Мячей */
	UFUNCTION(BlueprintImplementableEvent, Category = "Statistics", meta = (DisplayName = "BufferBallCounter"))
	void EventBufferBallCounter(const int32& Count);

	/**	Добавить количество Очков */
	void AddScore(const int32& iAddScore);

	/**	Event изменения количества Очков */
	UFUNCTION(BlueprintImplementableEvent, Category = "Statistics", meta = (DisplayName = "ScoreCounter"))
	void EventScoreCounter(const int32& Score);

	/**	Проверить количество всех мячей (на поле и в буфере) */
	void CheckAllBallsCounter();

	/**	Event изменения количества Жизней */
	UFUNCTION(BlueprintImplementableEvent, Category = "Statistics", meta = (DisplayName = "LivesCounter"))
	void EventLivesCounter(const int32& Lives);

	/**	Получить значение рекордного количества Очков */
	UFUNCTION(BlueprintCallable, Category = "Statistics")
	int32& GetRecordScore();
	//-------------------------------------------



	/* ---   Saving   --- */

	/**	Сохранение текущих данных игры */
	UFUNCTION(BlueprintCallable, Category = "Saving")
	void SaveCurrentGameData();

	/**	Получение данных игры */
	UFUNCTION(BlueprintCallable, Category = "Saving")
	FGameData LoadGameData();

	/**	Сохранение данных игры */
	UFUNCTION(BlueprintCallable, Category = "Saving")
	void ClearGameData();
	//-------------------------------------------



private:

	/* ---   Statistics   --- */

	// Указатель на текущую Каректу для проверки количества мячей в буффере
	AArk_VausPawn* CurrentVausPawn;

	// Количество Мячей в буфере
	int32 BufferBallCounter = 3;

	// Количество очков за игру
	int32 CurrentScore = 0;

	// Рекордное количество очков
	int32 RecordScore = 0;

	//
	
	/** Метод, хранящий действия при Окончании игры */
	void GameOver();

	//-------------------------------------------



	/* ---   Saving   --- */

	// Указатель на текущий SavingInstance
	USavingInstance* CurrentSavingInstance;
	//-------------------------------------------
};
