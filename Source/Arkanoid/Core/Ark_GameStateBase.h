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



/* ---   Delegates   --- */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLivesCounter, int32, Lives);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBufferBallCounter, int32, Count);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreCounter, int32, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOver, bool, bIsGameResult);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelWin, bool, bIsGameResult);
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

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

	//

	/**	Сохранить указатель на Каретку */
	void SetVausPawn(AArk_VausPawn* iPawn);

	/**	Изменить количество Мячей */
	void SetBufferBallCounter(const int32& Count);

	/**	Добавить количество Очков */
	void AddScore(const int32& iAddScore);

	/**	Проверить количество всех мячей (на поле и в буфере) */
	void CheckAllBallsCounter();

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



	/* ---   Saving   --- */

	/**	Сохранение текущих данных игры */
	UFUNCTION(BlueprintCallable, Category = "Saving")
	bool SaveCurrentGameData();

	/**	Получение данных игры */
	UFUNCTION(BlueprintCallable, Category = "Saving")
	FGameData LoadGameData();

	/**	Сохранение данных игры */
	UFUNCTION(BlueprintCallable, Category = "Saving")
	void ClearGameData();
	//-------------------------------------------



	/* ---   Levels Control   --- */

	// Список запускаемых уровней
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	TArray<TSoftObjectPtr<UWorld>> LevelsInOrder;

	// Номер текущего уровня
	int32 CurrentLevelNumber = 0;

	//

	/**	Переход на следующий уровень
	@note	Циклично по списку уровней "LevelsInOrder"
	*/
	UFUNCTION(BlueprintCallable, Category = "LevelsControl")
	void ToNextLevel();
	//-------------------------------------------



private:

	/* ---   Statistics   --- */

	// Указатель на текущую Каректу для проверки количества мячей в буффере
	AArk_VausPawn* CurrentVausPawn;

	// Количество Мячей в буфере (Обновляется Пешкой)
	int32 BufferBallCounter = 3;

	// Количество очков за игру
	int32 CurrentScore = 0;

	// Рекордное количество очков
	int32 RecordScore = 0;

	//

	/** Метод, хранящий действия при Окончании игры */
	void GameOver();

	/** Метод, хранящий действия при Уменьшении количества жизней */
	void DecLives();
	//-------------------------------------------



	/* ---   Saving   --- */

	// Указатель на текущий SavingInstance
	UArk_GameInstance* CurrentSavingInstance;

	/** Инициализация данных GameState */
	void Init();
	//-------------------------------------------
};
