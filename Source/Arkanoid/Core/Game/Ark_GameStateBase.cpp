// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Ark_GameStateBase.h"

// UE:
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"

// Interaction:
#include "Ark_PlayerController.h"
#include "Ark_VausPawn.h"
#include "Arkanoid/Core/Ark_GameInstance.h"
#include "Arkanoid/Elements/Ball.h"
#include "Arkanoid/Elements/Block.h"
#include "Arkanoid/Tools/Saving/SavedGameData.h"
//--------------------------------------------------------------------------------------



/* ---   Base   --- */

void AArk_GameStateBase::BeginPlay()
{
	Super::BeginPlay();

	Init();
}
//--------------------------------------------------------------------------------------



/* ---   Statistics   --- */

void AArk_GameStateBase::SetVausPawn(AArk_VausPawn* iPawn)
{
	CurrentVausPawn = iPawn;
}

void AArk_GameStateBase::SetBufferBallCounter(const int32& Count)
{
	BufferBallCounter = Count;

	OnBufferBallCounter.Broadcast(Count);
}

void AArk_GameStateBase::AddScore(const int32& iAddScore)
{
	CurrentScore += iAddScore;

	OnScoreCounter.Broadcast(CurrentScore);

	TArray<AActor*> lBlocks;

	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		ABlock::StaticClass(),
		lBlocks);

	if (lBlocks.Num() <= 1)
	{
		SaveLevelData();
		OnLevelWin.Broadcast(SaveGameData());
	}
}

void AArk_GameStateBase::CheckAllBallsCounter()
{
	if (CurrentVausPawn
		&& BufferBallCounter <= 0
		&& GetNumberBallsOnLevel() <= 1)
	{
		DecLives();

		if (CurrentLives < 0)
		{
			GameOver();
		}
		else
		{
			CurrentVausPawn->ResetDefaultTransform();
			CurrentVausPawn->AddBalls(1);
		}
	}
	else if (!CurrentVausPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("AArk_GameStateBase::CheckAllBallsCounter: CurrentVausPawn is NOT"));
	}
}

int32& AArk_GameStateBase::GetCurrentLives()
{
	return CurrentLives;
}

int32& AArk_GameStateBase::GetCurrentScore()
{
	return CurrentScore;
}

int32& AArk_GameStateBase::GetRecordScore()
{
	return RecordScore;
}

int32& AArk_GameStateBase::GetNumBufferBalls()
{
	return BufferBallCounter;
}

void AArk_GameStateBase::GameOver()
{
	ClearLevelData();
	OnGameOver.Broadcast(SaveGameData());
}

void AArk_GameStateBase::DecLives()
{
	--CurrentLives;

	OnLivesCounter.Broadcast(CurrentLives);
}

int32 AArk_GameStateBase::GetNumberBallsOnLevel()
{
	TArray<AActor*> lBalls;

	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		ABall::StaticClass(),
		lBalls);

	return lBalls.Num();
}
//--------------------------------------------------------------------------------------



/* ---   Game Instance   --- */

void AArk_GameStateBase::Init()
{
	/* ---   Game and Level Saving   --- */

	CurrentSavingInstance = GetWorld()->GetGameInstance<UArk_GameInstance>();

	if (!CurrentSavingInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("AArk_GameStateBase::Init: CurrentSavingInstance is NOT"));
	}

	UpdateGameData();
	UpdateLevelData();
	//-------------------------------------------
}
//--------------------------------------------------------------------------------------



/* ---   Game Saving   --- */

bool AArk_GameStateBase::SaveGameData()
{
	bool blResult = false;

	if (CurrentSavingInstance)
	{
		// Проверка нового рекорда
		if (CurrentScore > RecordScore)
		{
			FGameData lData;
			lData.RecordScore = CurrentScore;

			// Сохранение актуальных данных
			CurrentSavingInstance->SaveGameData(lData);

			blResult = true;
		}
	}

	return blResult;
}

void AArk_GameStateBase::UpdateGameData()
{
	if (CurrentSavingInstance)
	{
		FGameData lData = CurrentSavingInstance->LoadGameData();

		RecordScore = lData.RecordScore;
	}
}
//--------------------------------------------------------------------------------------



/* ---   Levels Saving   --- */

void AArk_GameStateBase::UpdateLevelData()
{
	if (CurrentSavingInstance)
	{
		FLevelData lData = CurrentSavingInstance->LoadLevelData();

		CurrentLives = lData.Lives > 0 ? lData.Lives : CurrentLives;
		CurrentScore = lData.Score > 0 ? lData.Score : CurrentScore;
		BufferBallCounter = lData.Balls > 0 ? lData.Balls : BufferBallCounter;

		// PS: Не сохраняем пустые данные
	}
}

void AArk_GameStateBase::SaveLevelData()
{
	if (CurrentSavingInstance)
	{
		FLevelData lData;

		lData.Lives = CurrentLives;
		lData.Score = CurrentScore;
		lData.Balls = BufferBallCounter + GetNumberBallsOnLevel();

		CurrentSavingInstance->SaveLevelData(lData);
	}
}

void AArk_GameStateBase::ClearLevelData()
{
	if (CurrentSavingInstance)
	{
		CurrentSavingInstance->SaveLevelData(FLevelData::Empty);
	}
}
//--------------------------------------------------------------------------------------
