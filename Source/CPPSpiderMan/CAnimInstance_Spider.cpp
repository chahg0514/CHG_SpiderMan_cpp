// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimInstance_Spider.h"

#include "CSpiderManPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CLandPredictionCurve.h"
#include "Curves/CurveFloat.h"
#include "UObject/ConstructorHelpers.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UCAnimInstance_Spider::UCAnimInstance_Spider()
{

	static ConstructorHelpers::FObjectFinder<UBlueprint> CurveAsset(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_CLandPredictionCurve.BP_CLandPredictionCurve'"));
	if (CurveAsset.Succeeded())
	{
		CurveFloat = (ACLandPredictionCurve*)CurveAsset.Object;
	}

}

void UCAnimInstance_Spider::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	MyPlayer = Cast<ACSpiderManPlayer>(TryGetPawnOwner());
	
}

void UCAnimInstance_Spider::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	
	if (IsValid(MyPlayer))
	{
		if (MyPlayer->GetIsLeftShift()) //쉬프트 누르고 있냐
		{
			isLeftShift = true;
			Speed = MyPlayer->GetVelocity().Size() / MyPlayer->GetCharacterMovement()->MaxWalkSpeed * 2;
			(Speed > 0.1) ? isMoving = true : isMoving = false;
		}
		else
		{
			isLeftShift = false;
			Speed = MyPlayer->GetVelocity().Size() / MyPlayer->GetCharacterMovement()->MaxWalkSpeed;
			(Speed > 0.1) ? isMoving = true : isMoving = false;
		}
		isWallRunning = MyPlayer->GetIsWallRunning();
		isAir = MyPlayer->GetCharacterMovement()->IsFalling();
		SetFallSpeed(DeltaSeconds);
		PredictLand(DeltaSeconds);
		isWebSwinging = MyPlayer->GetIsWebSwinging();
		SwingAngleAnim = MyPlayer->GetSwingAngle();
		SetAimOffsetValue();

	}
	
}

void UCAnimInstance_Spider::SetAimOffsetValue()
{
	FRotator Temp = UKismetMathLibrary::NormalizedDeltaRotator(MyPlayer->GetBaseAimRotation(), MyPlayer->GetActorRotation());
	Roll = Temp.Roll;
	Pitch = Temp.Pitch;
	Yaw = Temp.Yaw;
}

void UCAnimInstance_Spider::SetFallSpeed(float DeltaTime) //FallSpeed로 애니메이션
{
	FallSpeed = FMath::FInterpTo(FallSpeed, MyPlayer->GetCharacterMovement()->Velocity.Z * -1, DeltaTime, 5.f);
	LateralMovementSpeedAnim = MyPlayer->GetLateralMovementSpeed();
}

void UCAnimInstance_Spider::PredictLand(float DeltaTime) //현재 진행중인 방향에서 y쪽으로 틀어주고, 노멀라이즈한거에 또 값을 곱한벡터를 캐릭터위치에 더한걸 end로 한다
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), LandPredictionValue));

	if (MyPlayer->GetVelocity().Z < 0) //떨어지는 중일 때만 착지트레이스 발사
	{
		if (ZipToPointAnim == EZipToPointState::FlyForward) return;
		Start = MyPlayer->GetActorLocation();

		float ZVelocity = FMath::Clamp(MyPlayer->GetCharacterMovement()->Velocity.Z, -4000, -200);
		float MulValue = UKismetMathLibrary::MapRangeClamped(MyPlayer->GetCharacterMovement()->Velocity.Z, 0, -4000, 50, 2000);
		//떨어지는 속도에 비례해서 점점 더 먼 아래를 감지하되, 최대값은 정해줌
		
		FVector SecondVector = FVector(MyPlayer->GetCharacterMovement()->Velocity.X, MyPlayer->GetCharacterMovement()->Velocity.Y, ZVelocity).GetSafeNormal() * MulValue;
		End = Start + SecondVector;

		FHitResult HitResult;
		TArray<AActor*> IgnoreActors;


		if (UKismetSystemLibrary::CapsuleTraceSingle(GetWorld(), Start, End, 20.f, 40.f, UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
			IgnoreActors, EDrawDebugTrace::None, HitResult, true))
		{
			if ((HitResult.ImpactNormal - FVector(0, 0, 1)).Size() < 1.0) //이게 1보다 작다는건 경사가 완만하다는거니까 착지할 바닥임
			{
				LandPredictionValue = UKismetMathLibrary::MapRangeClamped(HitResult.Time, 0, 1, 1, 0);
			}
			
		}
		
	}
	else
	{
		LandPredictionValue = FMath::FInterpTo(LandPredictionValue, 0, DeltaTime, 0);
	}
}
