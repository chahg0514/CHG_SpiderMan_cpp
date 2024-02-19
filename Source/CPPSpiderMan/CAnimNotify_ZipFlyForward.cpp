// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_ZipFlyForward.h"
#include "CSpiderManPlayer.h"

void UCAnimNotify_ZipFlyForward::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	ACSpiderManPlayer* MyPlayer = Cast<ACSpiderManPlayer>(MeshComp->GetOwner());
	if (MyPlayer == nullptr) return;
	MyPlayer->FlyForward();

}
