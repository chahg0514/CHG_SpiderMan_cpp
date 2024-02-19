
// Fill out your copyright notice in the Description page of Project Settings.


//#include "BTTask_BossAttack.h"
//#include "CBoss_CatWoman.h"
//#include "CAIController_CatWoman.h"
//
//EBTNodeResult::Type UBTTask_BossAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	Super::ExecuteTask(OwnerComp, NodeMemory);
//	bNotifyTick = true;
//	
//	ACAIController_CatWoman* EnemyAIController = Cast<ACAIController_CatWoman>(OwnerComp.GetAIOwner());
//	if (EnemyAIController == nullptr)
//		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
//
//	ACBoss_CatWoman* Boss = Cast<ACBoss_CatWoman>(EnemyAIController->GetPawn());
//	if (Boss == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
//
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Execute"));
//	if (Boss->BossState == EBossCombatType::Patrol)
//	{
//		//Boss->SetNextAttackType(); //���� ���� ������ �Ÿ� ����, �̰� ���⼭ �����ְ� BTTask_SetAttackType���� �ű�. �� �Լ� ���ֵ� �ɵ�
//	}
//	IsArriveToPlayer = false;
//	
//	return EBTNodeResult::InProgress; //�̰� ����� Tick�� ���۵�
//}
//
//void UBTTask_BossAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
//{
//	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
//	
//
//	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Tick"));
//	ACAIController_CatWoman* EnemyAIController = Cast<ACAIController_CatWoman>(OwnerComp.GetAIOwner());
//	if (EnemyAIController == nullptr)
//		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
//
//	ACBoss_CatWoman* Boss = Cast<ACBoss_CatWoman>(EnemyAIController->GetPawn());
//	if (Boss == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
//
//	//���� ������ ���� �Ÿ��� �پ �� true�� �⺻���� ����
//	if (!IsArriveToPlayer)
//	{
//		if (Boss->MoveToPlayerByDistance()) //�̰� ��� �ݺ������� ����ż� ��������.
//		{
//			Boss->StartAttack();
//			//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); //�̰� ���������� �ؾ� �ֻ������ ���ư��� ����
//			IsArriveToPlayer = true;
//
//		}
//	}
//	
//
//
//
//}
