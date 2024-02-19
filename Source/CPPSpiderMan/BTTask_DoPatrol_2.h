// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DoPatrol_2.generated.h"

/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API UBTTask_DoPatrol_2 : public UBTTaskNode
{
	GENERATED_BODY()

private:
	float ExecuteTime = 0;
	float BeforeLeapTime = 0;
	FVector PatrolTarget;
public:
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	);
	virtual void TickTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory,
		float DeltaSeconds
	);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector isLeapKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector isCloseToLeap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float patrolTime = 5;
};
