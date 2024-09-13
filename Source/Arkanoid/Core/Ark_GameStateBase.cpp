// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Ark_GameStateBase.h"

// UE:
#include "Kismet/GameplayStatics.h"

// Interaction:
#include "Ark_PlayerController.h"
#include "Ark_VausPawn.h"
#include "Arkanoid/Tools/Saving/SavingInstance.h"
#include "Arkanoid/Tools/Saving/SavedGameData.h"
#include "Arkanoid/Elements/Ball.h"
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
}

void AArk_GameStateBase::CheckAllBallsCounter()
{
	if (CurrentVausPawn && CurrentVausPawn->NumBalls <= 0)
	{
		TArray<AActor*> lBalls;

		UGameplayStatics::GetAllActorsOfClass(
			GetWorld(),
			ABall::StaticClass(),
			lBalls);

		if (lBalls.Num() <= 1)
		{
			GameOver();
		}
	}
	else if (!CurrentVausPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("AArk_GameStateBase::CheckAllBallsCounter: CurrentVausPawn is NOT"));
	}
}

int32& AArk_GameStateBase::GetCurrentScore()
{
	return CurrentScore;
}

int32& AArk_GameStateBase::GetRecordScore()
{
	return RecordScore;
}

void AArk_GameStateBase::GameOver()
{
	OnGameOver.Broadcast(SaveCurrentGameData());
}
//--------------------------------------------------------------------------------------



/* ---   Saving   --- */

void AArk_GameStateBase::Init()
{
	CurrentSavingInstance = GetWorld()->GetGameInstance<USavingInstance>();

	if (CurrentSavingInstance)
	{
		RecordScore = LoadGameData().RecordScore;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AArk_GameStateBase::Init: CurrentSavingInstance is NOT"));
	}
}

bool AArk_GameStateBase::SaveCurrentGameData()
{
	bool blResult = false;

	if (CurrentSavingInstance)
	{
		FGameData lData;

		// Проверка нового рекорда
		if (RecordScore > CurrentScore)
		{
			lData.RecordScore = RecordScore;
		}
		else
		{
			lData.RecordScore = CurrentScore;
			blResult = true;
		}

		// Сохранение актуальных данных
		CurrentSavingInstance->SaveGameData(lData);
	}

	return blResult;
}

FGameData AArk_GameStateBase::LoadGameData()
{
	if (CurrentSavingInstance)
	{
		return CurrentSavingInstance->LoadGameData();
	}

	return FGameData::Empty;
}

void AArk_GameStateBase::ClearGameData()
{
	if (CurrentSavingInstance)
	{
		RecordScore = 0;

		CurrentSavingInstance->SaveGameData(FGameData::Empty);
	}
}
//--------------------------------------------------------------------------------------
