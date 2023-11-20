// Fill out your copyright notice in the Description page of Project Settings.


#include "CAttackMontage_Spider.h"
//#include "Engine/DataTable.h"

// Sets default values
ACAttackMontage_Spider::ACAttackMontage_Spider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataAsset(TEXT("/Script/Engine.DataTable'/Game/Character/Data/DT_AttackMontage_Spider.DT_AttackMontage_Spider'"));
	if (DataAsset.Succeeded())
	{
		MontageDataTable_2 = DataAsset.Object;
		MontageRowHandle_2.DataTable = DataAsset.Object;
		MontageRowHandle_2.RowName = TEXT("Bow"); //기본아이템, RowHandle은 특정 행
	}

}


