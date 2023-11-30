// Fill out your copyright notice in the Description page of Project Settings.


#include "CAN_EnableAttackMeshOverlap.h"
#include "CSpiderManPlayer.h"

void UCAN_EnableAttackMeshOverlap::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	ACSpiderManPlayer* MyPlayer = Cast<ACSpiderManPlayer>(MeshComp->GetOwner());
	if (MyPlayer == nullptr) return;
	MyPlayer->EnableAttackCollision(AttackPosition);
}
