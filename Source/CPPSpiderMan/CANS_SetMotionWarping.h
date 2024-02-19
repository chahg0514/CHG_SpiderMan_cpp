// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CANS_SetMotionWarping.generated.h"

/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API UCANS_SetMotionWarping : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
};
