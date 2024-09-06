// Fill out your copyright notice in the Description page of Project Settings.


#include "Ark_VausPawn.h"

// Sets default values
AArk_VausPawn::AArk_VausPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AArk_VausPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArk_VausPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AArk_VausPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

