#pragma once

// Base:
#include "CoreMinimal.h"
#include "Math/UnrealMath.h"

// UE:
#include "Engine/DataTable.h"

// Generated:
#include "LevelTableRow.generated.h"
//--------------------------------------------------------------------------------------



// Структура данных игры
USTRUCT(BlueprintType)
struct FLevelTableRow : public FTableRowBase
{
	GENERATED_BODY()

	// Название уровня
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	// Карта уровня
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> Map;
};
//--------------------------------------------------------------------------------------
