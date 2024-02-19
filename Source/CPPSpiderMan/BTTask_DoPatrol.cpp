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
//	Boss->SetCirclePatrolTargetVector(PatrolTarget); //���� bool�� Ȯ�� ���ص� ���ΰ����ϴ°� �ƴϸ� �� �ȹٲ�
//
//	if (Boss->MoveToPatrolVector()) //�����ϸ� �� �� : 
//	{
//
//	}
//
//
//	if (ExecuteTime > 5)
//	{
//		Boss->WhenEndStateCompletely(); //���⼭ patrol�� ������ �� ����
//		ExecuteTime = 0;
//		
//		EnemyAIController->SetFocus(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
//		//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//	}
//	
//	
//	//������ �ִٸ� ĳ���������� �����ؼ� �ٰ�����, ���ڸ����� Circle Patrol �ϱ�
//
//
//
//}
