// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossAttack_2.h"
#include "CBoss_CatWoman.h"
#include "CAIController_CatWoman.h"

EBTNodeResult::Type UBTTask_BossAttack_2::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	bNotifyTick = true;

	ACAIController_CatWoman* EnemyAIController = Cast<ACAIController_CatWoman>(OwnerComp.GetAIOwner());
	if (EnemyAIController == nullptr)
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	ACBoss_CatWoman* Boss = Cast<ACBoss_CatWoman>(EnemyAIController->GetPawn());
	if (Boss == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	Boss->SetIsArriveToAttackStartPosition(false);

	return EBTNodeResult::InProgress; //�̰� ����� Tick�� ���۵�
}

void UBTTask_BossAttack_2::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Tick"));
	ACAIController_CatWoman* EnemyAIController = Cast<ACAIController_CatWoman>(OwnerComp.GetAIOwner());
	if (EnemyAIController == nullptr)
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	ACBoss_CatWoman* Boss = Cast<ACBoss_CatWoman>(EnemyAIController->GetPawn());
	if (Boss == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	Boss->AttackTick();
	//���� ������ ���� �Ÿ��� �پ �� true�� �⺻���� ����
	
}
