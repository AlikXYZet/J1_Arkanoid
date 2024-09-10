// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Ark_GameStateBase.h"

// Interaction:
#include "Ark_PlayerController.h"
//--------------------------------------------------------------------------------------



/* ---   Statistics   --- */

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

}
//--------------------------------------------------------------------------------------
