// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// Interaction:
#include "Arkanoid/Tools/Saving/GameData.h"
#include "Arkanoid/Tools/Saving/LevelData.h"
#include "Arkanoid/Tools/TableRow/LevelTableRow.h"

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

	/* ---   Base   --- */

	/** Инициализация данных GameInstance */
	virtual void Init() override;
	//-------------------------------------------



	/* ---   Game Saving   --- */

	/** Сохранение игровых данных */
	void SaveGameData(const FGameData& iGameData) const;

	/** Получение игровых данных */
	FGameData LoadGameData() const;
	//-------------------------------------------



	/* ---   Level Saving   --- */

	/** Сохранение данных уровня */
	void SaveLevelData(const FLevelData& iLevelData);

	/** Получение данных уровня */
	FLevelData LoadLevelData() const;
	//-------------------------------------------



	/* ---   Levels Control   --- */

	// Список (таблица) запускаемых уровней
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	UDataTable* LevelTable;

	//

	/**	Запуск новой игры
	@note	Сбрасывает текущие данные игры и запускает первый уровень
	*/
	UFUNCTION(BlueprintCallable, Category = "LevelsControl")
	void ToNewGame(const int32 Select = 0);

	/**	Переход на следующий уровень
	@note	Циклично по списку уровней "LevelsInOrder"
	*/
	UFUNCTION(BlueprintCallable, Category = "LevelsControl")
	void ToNextLevel();

	/**	Получить отфильтрованный список уровней */
	UFUNCTION(BlueprintCallable, Category = "LevelsControl")
	TArray<FLevelTableRow> GetLevels();
	//-------------------------------------------



private:

	/* ---   Game Saving   --- */

	// Слот сохранения данных игры
	FString GameDataSlot = "GameData";

	// Сохраняемые данные Игры
	UPROPERTY()
	USavedGameData* SaveGame;

	//

	/** Инициализация метода сохранения данных игры */
	void GameSavingInit();

	/**	Обнуление данных игры */
	UFUNCTION(BlueprintCallable, Category = "Saving")
	void ClearGameData();
	//-------------------------------------------



	/* ---   Level Saving   --- */

	// Сохраняемые данные Уровня
	FLevelData LevelData;
	//-------------------------------------------



	/* ---   Levels Control   --- */

	// Список запускаемых уровней, полученный из таблицы
	TArray<FLevelTableRow> LevelsInOrder;

	// Номер текущего Уровня
	int32 CurrentLevelNumber = -1;

	//

	/** Инициализация метода управления уровнями */
	void LevelsControlInit();

	/**	Переход на выбранный уровень
	@note	Выбор из списка уровней "LevelsInOrder"
	*/
	void ToSelectedLevel(const int32& Select);
	//-------------------------------------------
};
