// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Ark_GameInstance.h"

// UE:
#include "Kismet/GameplayStatics.h"

// Interaction:
#include "Arkanoid/Tools/Saving/SavedGameData.h"
//--------------------------------------------------------------------------------------



/* ---   Game Saving   --- */

void UArk_GameInstance::Init()
{
	Super::Init();

	SaveGame = Cast<USavedGameData>(UGameplayStatics::LoadGameFromSlot(GameDataSlot, 0));

	if (!SaveGame)
	{
		SaveGame = Cast<USavedGameData>(UGameplayStatics::CreateSaveGameObject(
			USavedGameData::StaticClass()));

		SaveGameData(FGameData::Empty);
	}
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



/* ---   Levels Control   --- */

void UArk_GameInstance::SaveLevelNumber(const int32& iNumber)
{
	LevelNumber = iNumber;
}

int32 UArk_GameInstance::LoadLevelNumber()
{
	return LevelNumber;
}
//-------------------------------------------



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
