#pragma once

// Base:
#include "CoreMinimal.h"
#include "Math/UnrealMath.h"
// Generated:
#include "GameData.generated.h"
//--------------------------------------------------------------------------------------



// Структура данных игры
USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RecordScore = 0;

	// Пустой: Все значения структуры = 0
	static const FGameData Empty;
};
//--------------------------------------------------------------------------------------



/* ---   Переопределение для статических значений структуры   --- */

// Пустой: Все значения структуры = 0
__declspec(selectany) const FGameData FGameData::Empty {0};
//--------------------------------------------------------------------------------------