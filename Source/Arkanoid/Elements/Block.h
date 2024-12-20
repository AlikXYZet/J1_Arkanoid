// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Generated:
#include "Block.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

// Interaction:
class AGift;
//--------------------------------------------------------------------------------------



// Структура типа и шанса появления AGift
USTRUCT(BlueprintType)
struct FGiftType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<AGift> GiftType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AppearanceChance = 1.f;
};



UCLASS()
class ARKANOID_API ABlock : public AActor
{
	GENERATED_BODY()

public:

	/* ---   Constructors   --- */

	// Sets default values for this actor's properties
	ABlock();
	//-------------------------------------------



	/* ---   Components   --- */

	/** Меш визуализации мяча */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components,
		meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BlockMesh = nullptr;
	//-------------------------------------------



protected:

	/* ---   Base   --- */

	/** Переопределяемое собственное событие, определяющее начало игры для этого актера */
	virtual void BeginPlay() override;

	/** Вызывается, когда этот субъект явно уничтожается во время игрового процесса или в редакторе,
	* но не вызывается во время потоковой передачи уровней или завершения игрового процесса
	*/
	virtual void Destroyed() override;
	//-------------------------------------------



public:

	/* ---   Base   --- */

	/** Инициализация данных блока */
	void Init();
	//-------------------------------------------



	/* ---   Statistics   --- */

	/* Количество очков за блок */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters|Statistics")
	int32 ScoreNumber = 100;
	//-------------------------------------------



	/* ---   Lives   --- */

	// Звук уничтожения Блока
	UPROPERTY(EditAnywhere, Category = "Parameters|Lives")
	USoundBase* DestroySound = nullptr;

	// Массив материалов для каждого Уровня жизни блока
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters|Lives")
	TArray<UMaterialInterface*> LivesMaterials;

	//

	/** Установить материал блока согласно его уровню жизни
	и уменьшить количество оставшихся жизней
	@note	Запускает уничтожение Блока при Количестве оставшихся жизней меньше 0
	*/
	void ReductionLives();

	/** Получить количество жизней у данного блока */
	int32 GetNumLives() const;

	/** Воспроизвести звук уничтожения */
	void PlayDestroySound();

	/** Уничтожить блок с учётом необходимой логики */
	void DestroyBlock();
	//-------------------------------------------



	/* ---   Gift   --- */

	// Общий шанс появления Подарка
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters|Gift",
		meta = (ClampMin = "0", UIMin = "0"))
	float GiftChance = 0.1;

	// Массив создаваемых бонусов и антибонусов
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters|Gift",
		meta = (TitleProperty = GiftType))
	TArray<FGiftType> Gifts;

	//

	/** Создаёт подарок (бонус/антибонус) */
	void SpawnGift();
	//-------------------------------------------



private:

	/* ---   Statistics   --- */

	/** Добавить количества Очков */
	void AddScores();
	//-------------------------------------------



	/* ---   Lives   --- */

	// Количество "жизней" блока
	UPROPERTY()
	int32 NumLives = -1;
	//-------------------------------------------
};
