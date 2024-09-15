// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Ark_GameInstance.h"

// UE:
#include "Kismet/GameplayStatics.h"

// Interaction:
#include "Arkanoid/Tools/Saving/SavedGameData.h"
//--------------------------------------------------------------------------------------


void UArk_GameInstance::Init()
{
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
