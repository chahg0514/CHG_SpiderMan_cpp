// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance_CatWoman.generated.h"

/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API UCAnimInstance_CatWoman : public UAnimInstance
{
	GENERATED_BODY()

public:
	UCAnimInstance_CatWoman();
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = true))
		class ACBoss_CatWoman* MyPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		float Dir = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		float Speed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		bool isMoving = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		bool isAir = false;
public:

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
		bool isDeath = false;
};
