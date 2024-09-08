#include "MyRandom.h"

int32 GetRandom(const int32& min, const int32& max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);

	return distrib(gen);
}

bool GetRandom()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::bernoulli_distribution d(0.5);

	return d(gen);
}

float GetRandomFloat(const float& min, const float& max)
{
	return GetRandom(min * 256, max * 256) / static_cast<float>(256);
}
