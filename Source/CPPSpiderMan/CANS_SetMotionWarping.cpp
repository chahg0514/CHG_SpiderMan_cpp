// Fill out your copyright notice in the Description page of Project Settings.


#include "CANS_SetMotionWarping.h"
#include "CSpiderManPlayer.h"

void UCANS_SetMotionWarping::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	ACSpiderManPlayer* MyPlayer = Cast<ACSpiderManPlayer>(MeshComp->GetOwner());
	if (MyPlayer == nullptr) return;
	MyPlayer->SetMotionWarpingLoc();
}
