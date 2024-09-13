// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

// Interaction:
#include "GameData.h"

// Generated:
#include "SavedGameData.generated.h"
//--------------------------------------------------------------------------------------



UCLASS()
class ARKANOID_API USavedGameData : public USaveGame
{
	GENERATED_BODY()
	
public:

	// –екордное количество набранных очков за игру
	UPROPERTY(BlueprintReadOnly)
	FGameData GameData;
};
