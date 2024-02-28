// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DoPatrol_2.h"
#include "CBoss_CatWoman.h"
#include "CAIController_CatWoman.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_DoPatrol_2::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	bNotifyTick = true;

	ACAIController_CatWoman* EnemyAIController = Cast<ACAIController_CatWoman>(OwnerComp.GetAIOwner());
	if (EnemyAIController == nullptr)
		return EBTNodeResult::Failed;

	ACBoss_CatWoman* Boss = Cast<ACBoss_CatWoman>(EnemyAIController->GetPawn());
	

	if (Boss == nullptr) return EBTNodeResult::Failed;
	Boss->SetWalkSpeed(150);
	EnemyAIController->SetFocus(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Exucute"));
	return EBTNodeResult::InProgress;
}

void UBTTask_DoPatrol_2::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController_CatWoman* EnemyAIController = Cast<ACAIController_CatWoman>(OwnerComp.GetAIOwner());
	if (EnemyAIController == nullptr)
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	ACBoss_CatWoman* Boss = Cast<ACBoss_CatWoman>(EnemyAIController->GetPawn());
	if (Boss == nullptr) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	if (!IsSettingRecord)
	{
		ExecuteTime += DeltaSeconds / 3;

	}
	else
	{
		ExecuteTime += DeltaSeconds;

	}
	Boss->SetCirclePatrolTargetVector(PatrolTarget); //굳이 bool로 확인 안해도 새로갱신하는거 아니면 값 안바꿈

	if (Boss->MoveToPatrolVector()) //도착하면 할 거 : 
	{

	}
	if (EnemyAIController->GetBlackboardComponent()->GetValueAsBool(isCloseToLeap.SelectedKeyName))
	{
		BeforeLeapTime += DeltaSeconds;
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("%f"), BeforeLeapTime));
	}
	else
	{

	}
	if (BeforeLeapTime > 2)
	{
		
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("LeapOn"));
		BeforeLeapTime = 0;
		Boss->BossState = EBossState::Leap;
		EnemyAIController->GetBlackboardComponent()->SetValueAsBool(isLeapKey.SelectedKeyName, true);
		
	}
	if (ExecuteTime > patrolTime)
	{
		IsSettingRecord = true;
		if (Boss->IsCanAttack)
		{
			Boss->WhenEndStateCompletely(); //여기서 patrol을 제외한 것 선택
			ExecuteTime = 0;
			BeforeLeapTime = 0;

			EnemyAIController->ClearFocus(EAIFocusPriority::Gameplay);
		}
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("More5"));
		
		//EnemyAIController->ClearFocus();
		//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	
	//범위가 멀다면 캐릭터쪽으로 도약해서 다가가고, 제자리에서 Circle Patrol 하기



}

