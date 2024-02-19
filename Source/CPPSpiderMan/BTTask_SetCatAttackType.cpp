// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetCatAttackType.h"
#include "CBoss_CatWoman.h"
#include "CAIController_CatWoman.h"

EBTNodeResult::Type UBTTask_SetCatAttackType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController_CatWoman* EnemyAIController = Cast<ACAIController_CatWoman>(OwnerComp.GetAIOwner());
	if (EnemyAIController == nullptr) return EBTNodeResult::Failed;

	ACBoss_CatWoman* Boss = Cast<ACBoss_CatWoman>(EnemyAIController->GetPawn());
	if (Boss == nullptr) return EBTNodeResult::Failed;

	Boss->SetNextAttackType();

	return EBTNodeResult::Succeeded;
}
