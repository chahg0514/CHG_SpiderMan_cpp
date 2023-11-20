// Fill out your copyright notice in the Description page of Project Settings.


#include "CAN_DiableAttackMeshOverlap.h"
#include "CSpiderManPlayer.h"

void UCAN_DiableAttackMeshOverlap::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	ACSpiderManPlayer* MyPlayer = Cast<ACSpiderManPlayer>(MeshComp->GetOwner());
	if (MyPlayer == nullptr) return;
	MyPlayer->DisableAttackCollision();
}
