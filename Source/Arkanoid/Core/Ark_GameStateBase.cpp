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

	CurrentSavingInstance = Cast<USavingInstance>(
		UGameplayStatics::GetGameInstance(GetWorld()));

	FString lData = FString::FromInt(RecordScore);

	if (CurrentSavingInstance)
	{
		RecordScore = LoadGameData().RecordScore;

		lData = FString::FromInt(RecordScore);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AArk_GameStateBase::BeginPlay: CurrentSavingInstance is NOT"));
	}
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

	EventBufferBallCounter(Count);
}

void AArk_GameStateBase::AddScore(const int32& iAddScore)
{
	CurrentScore += iAddScore;

	EventScoreCounter(CurrentScore);
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

int32& AArk_GameStateBase::GetRecordScore()
{
	return RecordScore;
}

void AArk_GameStateBase::GameOver()
{
	SaveCurrentGameData();
}
//--------------------------------------------------------------------------------------



/* ---   Saving   --- */

void AArk_GameStateBase::SaveCurrentGameData()
{
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
		}

		// Сохранение актуальных данных
		CurrentSavingInstance->SaveGameData(lData);
	}
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
		CurrentSavingInstance->SaveGameData(FGameData::Empty);
	}
}
//--------------------------------------------------------------------------------------
