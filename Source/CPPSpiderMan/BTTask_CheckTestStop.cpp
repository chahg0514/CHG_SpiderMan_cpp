// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckTestStop.h"
#include "CAIController_CatWoman.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_CheckTestStop::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACAIController_CatWoman* EnemyAIController = Cast<ACAIController_CatWoman>(OwnerComp.GetAIOwner());
	if (EnemyAIController == nullptr)
		return EBTNodeResult::Failed; 

	APawn* Enemy = EnemyAIController->GetPawn();
	if (Enemy == nullptr) return EBTNodeResult::Failed;

	if (!isTest)
	{
		
		return EBTNodeResult::Failed;
	}
	else
	{
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Type();
}
