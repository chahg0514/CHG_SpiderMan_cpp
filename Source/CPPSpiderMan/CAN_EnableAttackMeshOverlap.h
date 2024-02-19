// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSpiderManPlayer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAN_EnableAttackMeshOverlap.generated.h"

/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API UCAN_EnableAttackMeshOverlap : public UAnimNotify
{
	GENERATED_BODY()
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere)
	struct FAttackPosition AttackPosition;
	
};