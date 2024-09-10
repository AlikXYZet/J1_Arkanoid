// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Generated:
#include "Gift.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

// UE:
class UProjectileMovementComponent;

// Interaction:
class AArk_VausPawn;
class ABall;
//--------------------------------------------------------------------------------------



UCLASS()
class ARKANOID_API AGift : public AActor
{
	GENERATED_BODY()

public:

	/* ---   Constructors   --- */

	// Sets default values for this actor's properties
	AGift();
	//-------------------------------------------



	/* ---   Components   --- */

	/** ��� ������������ ������� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GiftMesh = nullptr;

	/** ��������� ������������ ������� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	//-------------------------------------------



public:

	/* ---   Velocity   --- */

	// ��������� (���������) ��������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	float StartingVelocity = 100.f;
	//--------------------------------------------------------------------------------------



	/* ---   Collision   --- */

	/**	�������, ����� ���� ������� ������������� � ������ */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	//--------------------------------------------------------------------------------------



	/* ---   Reactions   --- */

	/**	������� �� ������ ������ */
	UFUNCTION(BlueprintImplementableEvent, Category = "Reactions", meta = (DisplayName = "Is Taken"))
	void EventIsTaken(AArk_VausPawn* VausPawn);

	/** �������� ��������� �� ����
	@warning	���� ���� �������� �� �������� ������. ���������� ����� ��������������
	*/
	UFUNCTION(BlueprintCallable, Category = "Reactions")
	TArray<ABall*> GetAllBalls();
	//--------------------------------------------------------------------------------------
};
