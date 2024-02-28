// Fill out your copyright notice in the Description page of Project Settings.


#include "CAN_Cat_SetMovementMode.h"
#include "CBoss_CatWoman.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAN_Cat_SetMovementMode::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	ACBoss_CatWoman* MyPlayer = Cast<ACBoss_CatWoman>(MeshComp->GetOwner());
	if (MyPlayer == nullptr) return;
	MyPlayer->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}
