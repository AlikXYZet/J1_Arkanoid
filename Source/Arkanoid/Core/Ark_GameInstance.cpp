﻿// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Ark_GameInstance.h"

// UE:
#include "Kismet/GameplayStatics.h"

// Interaction:
#include "Arkanoid/Tools/Saving/SavedGameData.h"
//--------------------------------------------------------------------------------------



/* ---   Base   --- */

void UArk_GameInstance::Init()
{
	Super::Init();

	GameSavingInit();
	LevelsControlInit();
}
//--------------------------------------------------------------------------------------



/* ---   Game Saving   --- */

void UArk_GameInstance::GameSavingInit()
{
	SaveGame = Cast<USavedGameData>(UGameplayStatics::LoadGameFromSlot(GameDataSlot, 0));

	if (!SaveGame)
	{
		SaveGame = Cast<USavedGameData>(UGameplayStatics::CreateSaveGameObject(
			USavedGameData::StaticClass()));

		SaveGameData(FGameData::Empty);
	}
}

void UArk_GameInstance::ClearGameData()
{
	SaveGameData(FGameData::Empty);
}

void UArk_GameInstance::SaveGameData(const FGameData& iGameData) const
{
	if (SaveGame)
	{
		SaveGame->GameData = iGameData;

		UGameplayStatics::SaveGameToSlot(SaveGame, GameDataSlot, 0);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UArk_GameInstance::SaveGameData: SaveGame is NOT"));
	}
}

FGameData UArk_GameInstance::LoadGameData() const
{
	if (SaveGame)
	{
		return SaveGame->GameData;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UArk_GameInstance::SaveGameData: SaveGame is NOT"));
	}

	return FGameData::Empty;
}
//--------------------------------------------------------------------------------------



/* ---   Level Saving   --- */

void UArk_GameInstance::SaveLevelData(const FLevelData& iLevelData)
{
	LevelData = iLevelData;
}

FLevelData UArk_GameInstance::LoadLevelData() const
{
	return LevelData;
}
//--------------------------------------------------------------------------------------



/* ---   Levels Control   --- */

void UArk_GameInstance::LevelsControlInit()
{
	// Фильтрация таблицы уровней в массив
	if (LevelTable
		&& LevelTable->GetRowStruct() == FLevelTableRow::StaticStruct())
	{
		LevelsInOrder.Empty();

		TArray<FLevelTableRow*> lFromTable;

		LevelTable->GetAllRows<FLevelTableRow>("Ark_GameStateBase::LevelTable", lFromTable);

		if (int32 lNum = lFromTable.Num())
		{
			FLevelTableRow* lRow = nullptr;

			// Фильтрация данных таблицы по валидности карты Уровня:
			for (int32 i = 0; i < lNum; ++i)
			{
				lRow = lFromTable[i];

				if (lRow->Map.GetAssetName().Len())
				{
					LevelsInOrder.Add(*lFromTable[i]);
				}
				else
				{
					UE_LOG(LogTemp, Warning,
						TEXT("AArk_GameStateBase::Init: Map in Row #%d from Table is NOT configured"),
						i + 1);
				}
			}
		}
	}
	else if (!LevelTable)
	{
		UE_LOG(LogTemp, Error, TEXT("AArk_GameStateBase::Init: LevelTable is NOT"));
	}
	else if (LevelTable->GetRowStruct() != FLevelTableRow::StaticStruct())
	{
		UE_LOG(LogTemp, Error, TEXT("AArk_GameStateBase::Init: LevelTable structure is NOT an FLevelTableRow"));
	}
}

void UArk_GameInstance::ToNewGame(const int32 iSelect)
{
	if (LevelsInOrder.IsValidIndex(iSelect))
	{
		SaveLevelData(FLevelData::Empty);
		ToSelectedLevel(CurrentLevelNumber = iSelect);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AArk_GameStateBase::ToNewGame: LevelsInOrder[%d] is NOT Valid"), iSelect);
	}
}

void UArk_GameInstance::ToNextLevel()
{
	if (LevelsInOrder.IsValidIndex(0))
	{
		if (0 <= CurrentLevelNumber && CurrentLevelNumber < LevelsInOrder.Num() - 1)
		{
			++CurrentLevelNumber;
		}
		else
		{
			CurrentLevelNumber = 0;
		}

		ToSelectedLevel(CurrentLevelNumber);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AArk_GameStateBase::ToNextLevel: LevelsInOrder[0] is NOT Valid"));
	}
}

TArray<FLevelTableRow> UArk_GameInstance::GetLevels()
{
	return LevelsInOrder;
}

void UArk_GameInstance::ToSelectedLevel(const int32& iSelect)
{
	if (LevelsInOrder.IsValidIndex(iSelect))
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), LevelsInOrder[iSelect].Map);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AArk_GameStateBase::ToSelectedLevel: LevelsInOrder[%d] is NOT Valid"), iSelect);
	}
}
//--------------------------------------------------------------------------------------
