#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// UE:
#include "Kismet/GameplayStatics.h"

// Generated:
#include "GeneratorBase.generated.h"
//--------------------------------------------------------------------------------------



UCLASS()
class ARKANOID_API AGeneratorBase : public AActor
{
	GENERATED_BODY()

public:

	/* ---   Constructors   --- */

	// Sets default values for this actor's properties
	AGeneratorBase();
	//-------------------------------------------



public:

	/* ---   Tools   --- */

	/** �������� ��� �������� (����� ��� ��� ����������) � ���������� �����

	@param  Tag -- ��� ����������. �� ��������� ���� (����� "")

	@return ������ ���������� ���������� ���� (����� ��� ��� ����������)
	���� ��������� �������� ��� ����� ����, �� Tag ������ ���� ������ (������ "")
	*/
	template<class T, class = std::enable_if<std::is_base_of<AActor, T>::value>::type>
	TArray<T*> GetAllActors(const FName& Tag = "")
	{
		TArray<T*> lResult;
		TArray<AActor*> lResultActors;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), T::StaticClass(), lResultActors);

		if (lResultActors.IsValidIndex(0))
		{
			for (AActor* lData : lResultActors)
			{
				T* lCurrentChessMan = Cast<T>(lData);

				if (Tag == "")
				{
					lResult.Add(lCurrentChessMan);
				}
				else
				{
					for (FName lTags : lCurrentChessMan->Tags)
					{
						if (lTags == Tag)
						{
							lResult.Add(lCurrentChessMan);
							break;
						}
					}
				}
			}
		}

		return lResult;
	}
	//-------------------------------------------
};
