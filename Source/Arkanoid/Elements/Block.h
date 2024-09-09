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
	TSubclassOf<AGift> GiftType;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BlockMesh = nullptr;
	//-------------------------------------------



protected:

	/* ---   Base   --- */

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//-------------------------------------------



public:

	/* ---   Destroyed   --- */

	// Массив материалов для каждого Уровня жизни блока
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
	TArray<UMaterial*> LivesMaterials;

	//

	/** Установить материал блока согласно его уровню жизни
	и уменьшить количество оставшихся жизней
	@note	Запускает уничтожение Блока при Количестве оставшихся жизней меньше 0
	*/
	void ReductionLives();
	//-------------------------------------------



	/* ---   Gift   --- */

	// Общий шанс появления Подарка
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gift")
	float GiftChance = 0.1;

	// Массив создаваемых бонусов и антибонусов
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gift")
	TArray<FGiftType> Gifts;

	//

	/** Создаёт подарок (бонус/антибонус) */
	void SpawnGift();
	//-------------------------------------------



private:

	/* ---   Destroyed   --- */

	// Количество "жизней" блока
	int32 NumLives = -1;

	//

	/** Вызывается, когда этот субъект явно уничтожается во время игрового процесса или в редакторе, но не вызывается во время потоковой передачи уровней или завершения игрового процесса */
	virtual void Destroyed() override;
	//-------------------------------------------
};
