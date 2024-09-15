#pragma once

// Base:
#include "CoreMinimal.h"
#include "Math/UnrealMath.h"

// Generated:
#include "LevelData.generated.h"
//--------------------------------------------------------------------------------------



// Структура данных игры
USTRUCT(BlueprintType)
struct FLevelData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Lives = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Balls = 0;



	/* ---   Static   --- */

	// Пустой: Все значения структуры равны базовымм значениям
	static const FLevelData Empty;
	//-------------------------------------------
};
//--------------------------------------------------------------------------------------



/* ---   Переопределение для статических значений структуры   --- */

// Пустой: Все значения структуры = 0
__declspec(selectany) const FLevelData FLevelData::Empty { 0, 0, 0 };
//--------------------------------------------------------------------------------------
