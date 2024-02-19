// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CheckTestStop.generated.h"

/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API UBTTask_CheckTestStop : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector isTestStopKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isTest;

	
};
