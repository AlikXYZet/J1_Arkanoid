﻿// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Block.h"

// UE:
#include "Kismet/GameplayStatics.h"

// Interaction:
#include "Arkanoid/Tools/MyRandom.h"
#include "Gift.h"
#include "Arkanoid/Core/Game/Ark_GameStateBase.h"
//--------------------------------------------------------------------------------------



/* ---   Constructors   --- */

// Sets default values
ABlock::ABlock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Предварительно



	/* ---   Components   --- */

	// Корневой компонент
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block Mesh"));
	RootComponent = BlockMesh;
	BlockMesh->SetRelativeScale3D(FVector(0.1f, 0.5f, 0.4f));
	BlockMesh->SetCastShadow(false);
	//-------------------------------------------
}
//--------------------------------------------------------------------------------------



/* ---   Base   --- */

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
}

void ABlock::Destroyed()
{
	// PS: В нашем случае, здесь логику лучше не прописывать, ибо она вызывается даже в Конструкторе
	Super::Destroyed();
}

void ABlock::Init()
{
	// Установить количество жизней блока и изменить материал
	NumLives = GetRandom(LivesMaterials.Num() - 1);
	ReductionLives();
}
//--------------------------------------------------------------------------------------



/* ---   Statistics   --- */

void ABlock::AddScores()
{
	if (AArk_GameStateBase* lCurrentArkGameState = GetWorld()->GetGameState<AArk_GameStateBase>())
	{
		lCurrentArkGameState->AddScore(ScoreNumber);
	}
}
//--------------------------------------------------------------------------------------



/* ---   Lives   --- */

void ABlock::ReductionLives()
{
	// Проверка на валидность элемента массива
	while (NumLives >= 0
		&& LivesMaterials.IsValidIndex(NumLives)
		&& LivesMaterials[NumLives] == nullptr)
	{
		--NumLives;
	}

	// Уничтожить или сменить материал
	if (NumLives < 0)
	{
		DestroyBlock();
	}
	else
	{
		BlockMesh->SetMaterial(0, LivesMaterials[NumLives]);
		--NumLives;
	}
}

int32 ABlock::GetNumLives() const
{
	return NumLives;
}

void ABlock::PlayDestroySound()
{
	if (DestroySound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), DestroySound);
	}
}

void ABlock::DestroyBlock()
{
	SpawnGift();
	AddScores();
	Destroy();
	PlayDestroySound();
}
//--------------------------------------------------------------------------------------



/* ---   Gift   --- */

void ABlock::SpawnGift()
{
	// Регулировка общего шанса появления
	if (GetRandom(GiftChance) && Gifts.IsValidIndex(0))
	{
		// Переменная расчёта шанса появления среди всех типов
		float lRand = 0;

		// Расчёт максимального значения
		for (FGiftType Data : Gifts)
		{
			if (Data.AppearanceChance > 0)
			{
				lRand += Data.AppearanceChance;
			}
		}

		// Получение шанса
		lRand = GetRandomFloat(lRand);

		// Выбор согласно шансу
		for (FGiftType Data : Gifts)
		{
			if (Data.AppearanceChance > 0)
			{
				lRand -= Data.AppearanceChance;

				if (lRand <= 0)
				{
					GetWorld()->SpawnActor<AGift>(
						Data.GiftType.Get(),
						GetActorLocation(),
						FRotator(0));

					break; // Выход из цикла
				}
			}
		}
	}
}
//--------------------------------------------------------------------------------------
