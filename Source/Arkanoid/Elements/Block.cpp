// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Block.h"

// Interaction:
#include "Arkanoid/Tools/MyRandom.h"
#include "Gift.h"
#include "Ball.h"
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
	//-------------------------------------------
}
//--------------------------------------------------------------------------------------



/* ---   Base   --- */

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();

	BlockMesh->OnComponentHit.AddDynamic(this, &ABlock::OnBlockHit);

	NumLives = GetRandom(0, LivesMaterials.Num() - 1);

	SetBlockMaterial();
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//--------------------------------------------------------------------------------------



/* ---   Destroyed   --- */

void ABlock::OnBlockHit(
	UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	if (OtherActor && Cast<ABall>(OtherActor))
	{
		SetBlockMaterial();
	}
	// PS: Возможно потребуется заменить "Cast" на группирование объектов по коллизии
}

void ABlock::Destroyed()
{
	SpawnGift();

	Super::Destroyed();
}

void ABlock::SetBlockMaterial()
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
		Destroy();
	}
	else
	{
		BlockMesh->SetMaterial(0, LivesMaterials[NumLives]);
		--NumLives;
	}
}

void ABlock::SpawnGift()
{
	GetWorld()->SpawnActor<AGift>(GetActorLocation(), FRotator());

	// PS: Требуется добавить шанс появления того или иного бонуса из конкретного списка
}
//--------------------------------------------------------------------------------------
