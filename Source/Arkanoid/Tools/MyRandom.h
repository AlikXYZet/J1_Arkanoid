#pragma once

#include "CoreMinimal.h"
#include <random>

// Получение рандомного значения [min, max]
int32 GetRandom(const int32& min, const int32& max);

// Получение рандомного bool значения
bool GetRandom();

// Получение рандомного float значения
float GetRandomFloat(const float& min = 0.f, const float& max = 1.f);
