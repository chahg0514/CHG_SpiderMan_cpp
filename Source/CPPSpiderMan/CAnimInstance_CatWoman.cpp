// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimInstance_CatWoman.h"

#include "CBoss_CatWoman.h"
#include "CSpiderManPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CLandPredictionCurve.h"
#include "Curves/CurveFloat.h"
#include "UObject/ConstructorHelpers.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "KismetAnimationLibrary.h"

UCAnimInstance_CatWoman::UCAnimInstance_CatWoman()
{


}

void UCAnimInstance_CatWoman::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	MyPlayer = Cast<ACBoss_CatWoman>(TryGetPawnOwner());

}

void UCAnimInstance_CatWoman::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (MyPlayer)
	{
		Speed = MyPlayer->GetVelocity().Size() / 150;
		(Speed > 0.1) ? isMoving = true : isMoving = false;
		Dir = UKismetAnimationLibrary::CalculateDirection(MyPlayer->GetVelocity(), MyPlayer->GetActorRotation());
		
	}
	
}

