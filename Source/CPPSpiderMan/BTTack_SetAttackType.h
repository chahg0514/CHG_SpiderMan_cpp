// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTack_SetAttackType.generated.h"

/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API UBTTack_SetAttackType : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	);
};
