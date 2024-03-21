// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttackMontage_Spider.generated.h"

namespace AttackMontageName
{

	const FName combo1 = TEXT("Combo1");
	const FName combo2 = TEXT("Combo2");
	const FName combo3 = TEXT("combo3");
	const FName combo4 = TEXT("combo4");


}

UCLASS()
class CPPSPIDERMAN_API ACAttackMontage_Spider : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACAttackMontage_Spider();


	//MSB3073, EditAnywhere 빼봄
private:
	//UPROPERTY(Category = "MontageData")
		class UDataTable* MontageDataTable_2;
	//UPROPERTY(Category = "MontageData")
		struct FDataTableRowHandle MontageRowHandle_2;

};
