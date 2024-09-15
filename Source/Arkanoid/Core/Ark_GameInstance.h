// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// Interaction:
#include "Arkanoid/Tools/Saving/GameData.h"
#include "Arkanoid/Tools/Saving/LevelData.h"

// Generated:
#include "Ark_GameInstance.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

// Interaction:
class USavedGameData;
//--------------------------------------------------------------------------------------



/**
 *
 */
UCLASS()
class ARKANOID_API UArk_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	/* ---   Game Saving   --- */

	/** Инициализация данных GameInstance */
	virtual void Init() override;

	/** Сохранение игровых данных */
	void SaveGameData(const FGameData& iGameData) const;

	/** Получение игровых данных */
	FGameData LoadGameData() const;
	//-------------------------------------------



	/* ---   Levels Control   --- */

	// Номер Уровня
	int32 LevelNumber = -1;

	//

	/** Сохранение номера Уровня */
	void SaveLevelNumber(const int32& iNumber);

	/** Получение номера Уровня */
	int32 LoadLevelNumber();
	//-------------------------------------------



	/* ---   Level Saving   --- */

	/** Сохранение данных уровня */
	void SaveLevelData(const FLevelData& iLevelData);

	/** Получение данных уровня */
	FLevelData LoadLevelData() const;
	//-------------------------------------------



private:

	/* ---   Game Saving   --- */

	// Слот сохранения данных игры
	FString GameDataSlot = "GameData";

	// Сохраняемые данные Игры
	UPROPERTY()
	USavedGameData* SaveGame;
	//-------------------------------------------



	/* ---   Level Saving   --- */

	// Сохраняемые данные Уровня
	FLevelData LevelData;
	//-------------------------------------------
};
