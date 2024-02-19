// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DoLeap.h"
#include "CBoss_CatWoman.h"
#include "CAIController_CatWoman.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_DoLeap::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	bNotifyTick = true;

	ACAIController_CatWoman* EnemyAIController = Cast<ACAIController_CatWoman>(OwnerComp.GetAIOwner());
	if (EnemyAIController == nullptr) return EBTNodeResult::Failed;
	EnemyAIController->SetFocus(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	LeapLocation = EnemyAIController->GetBlackboardComponent()->GetValueAsVector(LeapLocationKey.SelectedKeyName);

	ACBoss_CatWoman* Boss = Cast<ACBoss_CatWoman>(EnemyAIController->GetPawn());
	if (Boss == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	Boss->StartLeap();

	Boss->SetWarpTarget(BossMontageName::leap, LeapLocation);
	Boss->PlayWarpMontage(BossMontageName::leap);

	return EBTNodeResult::InProgress;
}

void UBTTask_DoLeap::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController_CatWoman* EnemyAIController2 = Cast<ACAIController_CatWoman>(OwnerComp.GetAIOwner());
	if (EnemyAIController2 == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	ACBoss_CatWoman* Boss = Cast<ACBoss_CatWoman>(EnemyAIController2->GetPawn());
	if (Boss == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	
	//Boss->LeapToLocation(LeapLocation);
}
