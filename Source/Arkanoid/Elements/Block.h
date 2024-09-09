// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Generated:
#include "Block.generated.h"
//--------------------------------------------------------------------------------------



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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block", NoClear)
	TArray<UMaterial*> LivesMaterials;

	//

	/** Установить материал блока согласно его уровню жизни
	и уменьшить количество оставшихся жизней
	@note	Запускает уничтожение Блока при Количестве оставшихся жизней меньше 0
	*/
	void ReductionLives();
	//-------------------------------------------



private:

	/* ---   Destroyed   --- */

	// Количество "жизней" блока
	int32 NumLives = -1;

	//

	/** Вызывается, когда этот субъект явно уничтожается во время игрового процесса или в редакторе, но не вызывается во время потоковой передачи уровней или завершения игрового процесса */
	virtual void Destroyed() override;

	/** Создаёт подарок (бонус/антибонус) */
	void SpawnGift();
	//-------------------------------------------
};
