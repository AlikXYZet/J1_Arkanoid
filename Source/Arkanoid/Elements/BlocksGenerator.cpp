// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "BlocksGenerator.h"

// Interaction:
#include "Block.h"
//--------------------------------------------------------------------------------------



/* ---   Constructors   --- */

// Sets default values
ABlocksGenerator::ABlocksGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Предварительно
}
//--------------------------------------------------------------------------------------



/* ---   Base   --- */

// Called when the game starts or when spawned
void ABlocksGenerator::BeginPlay()
{
	Super::BeginPlay();



	/* ---   Generator   --- */

	StartGenerator();
	//-------------------------------------------
}
//--------------------------------------------------------------------------------------



/* ---   Generator   --- */

void ABlocksGenerator::StartGenerator()
{
	// Лямбда-выражение
	std::function<const bool(const int32&, const int32&)> lLambda
		= [](const int32&, const int32&) { return false; };

	// Выбор критерия 
	switch (GenerationType)
	{
	case EGenerationType::Tight: // Плотная компоновка
		lLambda = [](const int32&, const int32&)
			{ return true; };
		break;

	case EGenerationType::XType: // X-компоновка
		lLambda = [&](const int32& x, const int32& y)
			{ return x == y || x == NumberAlongAxes.Y - 1 - y; };
		break;

	case EGenerationType::Chess: // В шахматном порядке
		lLambda = [](const int32& x, const int32& y)
			{ return bool((x + y) % 2); };
		break;

	default: // Один блок в середине (примерно)
		lLambda = [&](const int32& x, const int32& y)
			{ return x == NumberAlongAxes.X / 2 && y == NumberAlongAxes.Y / 2; };
		break;
	}

	// Генерация по выбранному критерию
	CreateGeneratedBlocks(lLambda);
}

void ABlocksGenerator::CreateGeneratedBlocks(const std::function<const bool(const int32&, const int32&)>& iFunction)
{
	for (int32 x = 0; x < NumberAlongAxes.X; ++x)
	{
		for (int32 y = 0; y < NumberAlongAxes.Y; ++y)
		{
			if (iFunction(x, y))
			{
				CreateBlock(FIndex2D(x, y));
			}
		}
	}
}

void ABlocksGenerator::CreateBlock(const FIndex2D& iXY)
{
	ABlock* lBlock = GetWorld()->SpawnActor<ABlock>(BlockType.Get(), FTransform());

	CheckData(lBlock);

	lBlock->SetActorLocation(GetLocationForBlock(iXY));
}

void ABlocksGenerator::CheckData(const ABlock* ipBlock)
{
	if (BlockSize.IsZero())
	{
		BlockSize = ipBlock->BlockMesh->GetRelativeScale3D() * 100.f;

		PointOffset = FVector(
			0,
			(BlockSize.Y + Gap.Y) * (NumberAlongAxes.Y - 1) / 2,
			BlockSize.Z / 2);
	}
}

FVector ABlocksGenerator::GetLocationForBlock(const FIndex2D& iXY) const
{
	if (NumberAlongAxes.Within(iXY))
	{
		return (BlockSize + Gap) * iXY - PointOffset + GetActorLocation();
		//return (BlockSize + Gap) * iXY + PointOffset;
	}

	return FVector::ZeroVector;
}
//--------------------------------------------------------------------------------------
