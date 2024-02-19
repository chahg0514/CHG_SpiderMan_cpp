// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAN_ApplyDamageCatBasic.generated.h"

/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API UCAN_ApplyDamageCatBasic : public UAnimNotify
{
	GENERATED_BODY()
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
