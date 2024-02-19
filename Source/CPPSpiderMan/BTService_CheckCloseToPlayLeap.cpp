// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckCloseToPlayLeap.h"
#include "AIController.h"
#include "CBoss_CatWoman.h"
#include "CAIController_CatWoman.h"
#include "BehaviorTree/BlackboardComponent.h"


void UBTService_CheckCloseToPlayLeap::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (OwnerComp.GetAIOwner() == nullptr) return;

	ACAIController_CatWoman *aiController = Cast<ACAIController_CatWoman>(OwnerComp.GetAIOwner());
	if (!aiController) return;
	ACBoss_CatWoman *catWoman = Cast<ACBoss_CatWoman>(OwnerComp.GetAIOwner()->GetPawn());
	if (!catWoman) return;

	
	aiController->GetBlackboardComponent()->SetValueAsBool(isCloseKey.SelectedKeyName, catWoman->IsCloseToPlayer());
}
