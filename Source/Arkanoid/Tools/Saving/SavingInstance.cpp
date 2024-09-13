// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "SavingInstance.h"

// UE:
#include "Kismet/GameplayStatics.h"

// Interaction:
#include "SavedGameData.h"
//--------------------------------------------------------------------------------------


void USavingInstance::Init()
{
	SaveGame = Cast<USavedGameData>(UGameplayStatics::LoadGameFromSlot(GameDataSlot, 0));

	if (!SaveGame)
	{
		SaveGame = Cast<USavedGameData>(UGameplayStatics::CreateSaveGameObject(
			USavedGameData::StaticClass()));

		SaveGameData(FGameData::Empty);
	}
}

void USavingInstance::SaveGameData(const FGameData& iGameData) const
{
	if (SaveGame)
	{
		SaveGame->GameData = iGameData;

		UGameplayStatics::SaveGameToSlot(SaveGame, GameDataSlot, 0);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("USavingInstance::SaveGameData: SaveGame is NOT"));
	}
}

FGameData USavingInstance::LoadGameData() const
{
	if (SaveGame)
	{
		return SaveGame->GameData;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("USavingInstance::SaveGameData: SaveGame is NOT"));
	}

	return FGameData::Empty;
}
