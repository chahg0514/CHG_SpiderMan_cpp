// Fill out your copyright notice in the Description page of Project Settings.


#include "CANS_SetOverlapWhenAttack.h"
#include "CSpiderManPlayer.h"

void UCANS_SetOverlapWhenAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	ACSpiderManPlayer* MyPlayer = Cast<ACSpiderManPlayer>(MeshComp->GetOwner());
	if (MyPlayer == nullptr) return;
	MyPlayer->SetMotionWarpingLoc();

}

void UCANS_SetOverlapWhenAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	ACSpiderManPlayer* MyPlayer = Cast<ACSpiderManPlayer>(MeshComp->GetOwner());
	if (MyPlayer == nullptr) return;
	MyPlayer->DisableAttackCollision();
}

void UCANS_SetOverlapWhenAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("NotifyTick"));
}
