// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

// Generated:
#include "Ark_GameStateBase.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

// Interaction:
class AArk_VausPawn;
class AArk_PlayerController;
//--------------------------------------------------------------------------------------



UCLASS()
class ARKANOID_API AArk_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

protected:

	


public:
	TSubclassOf<AArk_PlayerController> CurrentPlayerController = nullptr;
	/* ---   Statistics   --- */

	// Количество жизней
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	int32 CurrentLives = 3;

	//

	/**	Изменить количество Мячей */
	void SetBufferBallCounter(const int32& Count);

	/**	Event изменения количества Мячей */
	UFUNCTION(BlueprintImplementableEvent, Category = "Status", meta = (DisplayName = "BufferBallCounter"))
	void EventBufferBallCounter(const int32& Count);

	/**	Добавить количество Очков */
	void AddScore(const int32& iAddScore);

	/**	Event изменения количества Очков */
	UFUNCTION(BlueprintImplementableEvent, Category = "Status", meta = (DisplayName = "ScoreCounter"))
	void EventScoreCounter(const int32& Score);

	/**	Проверить количество всех мячей (на поле и в буфере) */
	void CheckAllBallsCounter();

	/**	Event изменения количества Жизней */
	UFUNCTION(BlueprintImplementableEvent, Category = "Status", meta = (DisplayName = "LivesCounter"))
	void EventLivesCounter(const int32& Lives);
	//--------------------------------------------------------------------------------------



private:

	/* ---   Statistics   --- */

	// Количество Мячей в буфере
	int32 BufferBallCounter = 3;

	// Количество очков за игру
	int32 CurrentScore = 0;
	//--------------------------------------------------------------------------------------
};
