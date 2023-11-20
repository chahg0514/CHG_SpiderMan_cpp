// Fill out your copyright notice in the Description page of Project Settings.


//#include "BTTask_DoPatrol.h"
//#include "CBoss_CatWoman.h"
//#include "CAIController_CatWoman.h"
//#include "Kismet/GameplayStatics.h"
//
//EBTNodeResult::Type UBTTask_DoPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	Super::ExecuteTask(OwnerComp, NodeMemory);
//	bNotifyTick = true;
//	
//	ACAIController_CatWoman* EnemyAIController = Cast<ACAIController_CatWoman>(OwnerComp.GetAIOwner());
//	if (EnemyAIController == nullptr)
//		return EBTNodeResult::Failed;
//
//	ACBoss_CatWoman* Boss = Cast<ACBoss_CatWoman>(EnemyAIController->GetPawn());
//
//
//	if (Boss == nullptr) return EBTNodeResult::Failed;
//	Boss->SetWalkSpeed(100);
//	EnemyAIController->SetFocus(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
//	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Exucute"));
//	return EBTNodeResult::InProgress;
//}
//
//void UBTTask_DoPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
//{
//	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
//
//	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Patrollll"));
//	ACAIController_CatWoman* EnemyAIController = Cast<ACAIController_CatWoman>(OwnerComp.GetAIOwner());
//	if (EnemyAIController == nullptr)
//		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
//
//
//
//	ACBoss_CatWoman* Boss = Cast<ACBoss_CatWoman>(EnemyAIController->GetPawn());
//	if (Boss == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
//
//	ExecuteTime += DeltaSeconds;
//
//	Boss->SetCirclePatrolTargetVector(PatrolTarget); //굳이 bool로 확인 안해도 새로갱신하는거 아니면 값 안바꿈
//
//	if (Boss->MoveToPatrolVector()) //도착하면 할 거 : 
//	{
//
//	}
//
//
//	if (ExecuteTime > 5)
//	{
//		Boss->WhenEndStateCompletely(); //여기서 patrol을 제외한 것 선택
//		ExecuteTime = 0;
//		
//		EnemyAIController->SetFocus(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
//		//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//	}
//	
//	
//	//범위가 멀다면 캐릭터쪽으로 도약해서 다가가고, 제자리에서 Circle Patrol 하기
//
//
//
//}
