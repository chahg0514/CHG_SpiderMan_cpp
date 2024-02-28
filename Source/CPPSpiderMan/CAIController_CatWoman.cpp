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
	PrimaryActorTick.bCanEverTick = true; //ƽ�Լ� Ȱ��ȭ
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"))); //�ۼ��� ������Ʈ ���� 
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComp"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAsset(TEXT("/Script/AIModule.BehaviorTree'/Game/catwoman__1_/AI/BT_Boss.BT_Boss'"));
	if (BTAsset.Succeeded())
	{
		BTree = BTAsset.Object;
	}
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig")); //�þ� ���� ��ü ����
	SightConfig->SightRadius = 1000.f; //�� �� �ִ� ����
	SightConfig->LoseSightRadius = 1050.f; //�̹� �� ��ǥ���� �� �� �ִ� ����
	SightConfig->SetMaxAge(3.0f); //�� �� �ִ� �ð�
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation()); //�����켱������ �þ߷� ����
	GetPerceptionComponent()->ConfigureSense(*SightConfig); //�þ� ���� ���
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ACAIController_CatWoman::OnTargetDetected); //�þ߹����� ���Դٸ� OnTargetDetected �Լ� ȣ��

	SightConfig->DetectionByAffiliation.bDetectNeutrals = true; //�߸� ����


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
		GetPerceptionComponent()->GetCurrentlyPerceivedActors(AISense, Actors); //������ ���͸� ��� �迭�� �־���
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
