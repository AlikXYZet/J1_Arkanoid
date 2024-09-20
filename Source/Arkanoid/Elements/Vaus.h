// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Generated:
#include "Vaus.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

// Interaction:
class AArk_VausPawn;
//--------------------------------------------------------------------------------------



UCLASS()
class ARKANOID_API AVaus : public AActor
{
	GENERATED_BODY()

public:

	/* ---   Constructors   --- */

	// Sets default values for this actor's properties
	AVaus();
	//-------------------------------------------



	/* ---   Components   --- */

	/** ��� ������������ ������� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* VausMesh = nullptr;

	/** ��� ������������ ������� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftMesh = nullptr;

	/** ��� ������������ ������� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightMesh = nullptr;
	//-------------------------------------------



protected:

	/* ---   Base   --- */

	/** ���������������� ����������� �������, ������������ ������ ���� ��� ����� ������ */
	void virtual BeginPlay() override;
	//-------------------------------------------



public:

	/* ---   Gift   --- */

	// ����������� ������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters", meta = (ClampMin = "0.1", UIMin = "0.1"))
	float MinWidth = 0.5f;

	//

	/** ���������� ������ ������� */
	void AddWidth(const float AddValue = 0.1f);

	/** ����� ������ ������� */
	void ResetWidth();

	/** �������� ��������� �� �����, �������� ����������� */
	void SetPawnPointer(AArk_VausPawn* iVausPawn);

	/** �������� ��������� �� �����, �������� ����������� */
	AArk_VausPawn* GetPawnPointer();
	//-------------------------------------------



private:

	/* ---   Gift   --- */

	// ������� �������, ���������� �� VausMesh
	FVector BaseScale3D = FVector(0.1f, 1.f, 0.4f);

	// ��������� �� �����, �������� �����������
	AArk_VausPawn* pVausPawn;

	//

	void UpdateSecondaryMeshLocation();
	//-------------------------------------------
};
