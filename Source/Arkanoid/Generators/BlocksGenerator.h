// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GeneratorBase.h"

// C++:
#include <functional> // Для предиката

// Interaction:
#include "Arkanoid/Tools/Index2D.h"

// Generated:
#include "BlocksGenerator.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

class ABlock;
//--------------------------------------------------------------------------------------



// Тип Генерации
UENUM(BlueprintType)
enum struct EGenerationType : uint8
{
	NONE = 0,
	// X-компоновка
	XType,
	// Компоновка колоннами через 1
	Column,
	// Компоновка рядами через 1
	Row,
	// В шахматном порядке
	Chess,
	// Плотная компоновка (полное заполнение)
	Tight,
	// Рандомная компоновка из списка
	Random,
};



UCLASS()
class ARKANOID_API ABlocksGenerator : public AGeneratorBase
{
	GENERATED_BODY()

public:

	/* ---   Constructors   --- */

	// Sets default values for this actor's properties
	ABlocksGenerator();
	//-------------------------------------------



protected:

	/* ---   Base   --- */

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//-------------------------------------------



public:

	/* ---   Generator   --- */

	// Тег верификации для определения компонента, созданного текущим генератором
	FName VerificationTag = FName(GetNameSafe(this));

	// Перегенерировать при старте уровня?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generator")
	bool RegenerateAtStartup = true;

	// Тип генерации
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generator")
	EGenerationType GenerationType;

	// Тип генерируемого блока
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generator")
	TSubclassOf<ABlock> BlockType;

	// Зазор между блоками
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generator")
	FVector Gap = { 10.f, 10.f, 2.5f };

	// Количество вдоль осей
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generator",
		meta = (ClampMin = "1", UIMin = "1"))
	FIndex2D NumberAlongAxes = { 10, 10 };

	//

	/** Перегенерировать (перезапустить) данный Генератор */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Generator")
	void ReGenerate();

	/** Удалить все блоки */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Generator")
	void DeleteAllBlocks();
	//-------------------------------------------



private:

	/* ---   Generator   --- */

	// Вычисленный размер блока
	FVector BlockSize = FVector::ZeroVector;

	// Вычисленное смещение точки
	FVector PointOffset = FVector::ZeroVector;

	//

	/** Запуск генерации блоков */
	void StartGenerator();

	/** Запуск генерации блоков */
	void CreateGeneratedBlocks(const std::function<const bool(const int32&, const int32&)>& iFunction);

	/** Создать блок в указанной позиции */
	void CreateBlock(const FIndex2D& iXY);

	/** Проверить данные, при необходимости обновляет их по актору */
	void CheckGeneratorData(const ABlock* ipBlock);

	/** Получить локацию блока с указанным индексом матрицы */
	FVector GetLocationForBlock(const FIndex2D& iXY) const;
	//-------------------------------------------
};
