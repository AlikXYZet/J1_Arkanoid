// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// Interaction:
#include "Arkanoid/Tools/Saving/GameData.h"

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
	
	virtual void Init() override;

	FString GameDataSlot = "GameData";

	UPROPERTY()
	USavedGameData* SaveGame;

public:

	void SaveGameData(const FGameData& iGameData) const;

	FGameData LoadGameData() const;
};
