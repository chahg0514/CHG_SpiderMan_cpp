// Fill out your copyright notice in the Description page of Project Settings.


#include "CAN_CatSetFocus.h"
#include "CBoss_CatWoman.h"

void UCAN_CatSetFocus::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	ACBoss_CatWoman* MyPlayer = Cast<ACBoss_CatWoman>(MeshComp->GetOwner());
	if (MyPlayer == nullptr) return;
	MyPlayer->SetFocusToTarget();
}
