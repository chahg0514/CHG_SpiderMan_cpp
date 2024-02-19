// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BossAttack_2.generated.h"

/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API UBTTask_BossAttack_2 : public UBTTaskNode
{
	GENERATED_BODY()
private:
	

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
	
};
