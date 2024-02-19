// Fill out your copyright notice in the Description page of Project Settings.


#include "CANS_CatBasicAttackMovement.h"
#include "CBoss_CatWoman.h"

void UCANS_CatBasicAttackMovement::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	ACBoss_CatWoman* MyPlayer = Cast<ACBoss_CatWoman>(MeshComp->GetOwner());
	if (MyPlayer == nullptr) return;
	MyPlayer->BasicAttackLaunch();
}
