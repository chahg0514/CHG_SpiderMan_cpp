// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_FreezeInAir.h"
#include "CSpiderManPlayer.h"


void UCAnimNotify_FreezeInAir::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	ACSpiderManPlayer* MyPlayer = Cast<ACSpiderManPlayer>(MeshComp->GetOwner());
	if (MyPlayer == nullptr) return;
	MyPlayer->ShootWebs();
}
