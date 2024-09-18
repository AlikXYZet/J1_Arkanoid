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
class UParticleSystemComponent;

// Plugins:
class UNiagaraComponent;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* FXComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* NiagaraFXComponent = nullptr;
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
	//--------------------------------------------------------------------------------------
};
