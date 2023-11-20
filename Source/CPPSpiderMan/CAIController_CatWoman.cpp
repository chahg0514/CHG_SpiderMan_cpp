// Fill out your copyright notice in the Description page of Project Settings.


#include "CAIController_CatWoman.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BlackboardKeys_Boss.h"
#include "CSpiderManPlayer.h"
#include "Kismet/GameplayStatics.h"

ACAIController_CatWoman::ACAIController_CatWoman()
{
	PrimaryActorTick.bCanEverTick = true; //틱함수 활성화
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"))); //퍼셉션 컴포넌트 생성 
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComp"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAsset(TEXT("/Script/AIModule.BehaviorTree'/Game/catwoman__1_/AI/BT_Boss.BT_Boss'"));
	if (BTAsset.Succeeded())
	{
		BTree = BTAsset.Object;
	}
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig")); //시야 정보 객체 생성
	SightConfig->SightRadius = 1000.f; //볼 수 있는 범위
	SightConfig->LoseSightRadius = 1050.f; //이미 본 목표물을 볼 수 있는 범위
	SightConfig->SetMaxAge(3.0f); //볼 수 있는 시간
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation()); //감지우선순위를 시야로 설정
	GetPerceptionComponent()->ConfigureSense(*SightConfig); //시야 정보 등록
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ACAIController_CatWoman::OnTargetDetected); //시야범위에 들어왔다면 OnTargetDetected 함수 호출

	SightConfig->DetectionByAffiliation.bDetectNeutrals = true; //중립 감지


	Target = Cast<ACSpiderManPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	GetBlackboardComponent()->SetValueAsObject(BBKeysBoss::target, Target);
}

void ACAIController_CatWoman::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (!BTree) return;
	RunBehaviorTree(BTree);
	if (!Blackboard) return;
	Blackboard->InitializeBlackboard(*BTree->BlackboardAsset);

}

void ACAIController_CatWoman::OnTargetDetected(AActor* InActor, FAIStimulus Stimulus)
{
	

	if (InActor->ActorHasTag("Player"))
	{
		GetBlackboardComponent()->SetValueAsBool(BBKeysBoss::isFindPlayer, Stimulus.WasSuccessfullySensed());
		TSubclassOf<UAISense> AISense;
		TArray<AActor*> Actors;
		GetPerceptionComponent()->GetCurrentlyPerceivedActors(AISense, Actors); //감지된 액터를 모두 배열에 넣어줌
		for (auto Other : Actors)
		{
			if (ACSpiderManPlayer* MyPlayer = Cast<ACSpiderManPlayer>(Other))
			{
				GetBlackboardComponent()->SetValueAsObject(BBKeysBoss::target, MyPlayer);
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Goodd"));
			}
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Fail!!!"));
	}

}
