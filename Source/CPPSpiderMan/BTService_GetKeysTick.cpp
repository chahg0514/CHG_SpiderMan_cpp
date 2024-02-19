// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_GetKeysTick.h"
#include "CBoss_CatWoman.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include "CAIController_CatWoman.h"
#include "AIController.h"
#include "CAIController_CatWoman.h"
#include "BlackboardKeys_Boss.h"

void UBTService_GetKeysTick::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetAIOwner() == nullptr) return;

	aiController = Cast<ACAIController_CatWoman>(OwnerComp.GetAIOwner());
	if (!aiController) return;

	catWoman = Cast<ACBoss_CatWoman>(OwnerComp.GetAIOwner()->GetPawn());
	if (!catWoman) return;

	aiController->GetBlackboardComponent()->SetValueAsBool(isHitKey.SelectedKeyName, catWoman->BossState == EBossState::Stunned);
	aiController->GetBlackboardComponent()->SetValueAsBool(isSetAttackType.SelectedKeyName, catWoman->isSetAttackType);
	aiController->GetBlackboardComponent()->SetValueAsBool(isPatrolKey.SelectedKeyName, catWoman->BossState == EBossState::Patrol);
	aiController->GetBlackboardComponent()->SetValueAsBool(isLeapKey.SelectedKeyName, catWoman->BossState == EBossState::Leap);
	if (catWoman->BossState == EBossState::Leap)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("LeapTrue"));
	}

	

	

	
	

}
