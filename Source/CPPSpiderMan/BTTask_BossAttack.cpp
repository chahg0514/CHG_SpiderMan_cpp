
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
//		//Boss->SetNextAttackType(); //다음 공격 종류와 거리 설정, 이거 여기서 안해주고 BTTask_SetAttackType으로 옮김. 이 함수 없애도 될듯
//	}
//	IsArriveToPlayer = false;
//	
//	return EBTNodeResult::InProgress; //이걸 해줘야 Tick이 시작됨
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
//	//공격 종류에 따른 거리로 뛰어간 후 true면 기본공격 실행
//	if (!IsArriveToPlayer)
//	{
//		if (Boss->MoveToPlayerByDistance()) //이게 계속 반복적으로 실행돼서 문제였음.
//		{
//			Boss->StartAttack();
//			//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); //이걸 실행중으로 해야 최상단으로 돌아가지 않음
//			IsArriveToPlayer = true;
//
//		}
//	}
//	
//
//
//
//}
