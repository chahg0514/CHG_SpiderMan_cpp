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
		if (MyPlayer->GetIsLeftShift()) //����Ʈ ������ �ֳ�
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

void UCAnimInstance_Spider::SetFallSpeed(float DeltaTime) //FallSpeed�� �ִϸ��̼�
{
	FallSpeed = FMath::FInterpTo(FallSpeed, MyPlayer->GetCharacterMovement()->Velocity.Z * -1, DeltaTime, 5.f);
	LateralMovementSpeedAnim = MyPlayer->GetLateralMovementSpeed();
}

void UCAnimInstance_Spider::PredictLand(float DeltaTime) //���� �������� ���⿡�� y������ Ʋ���ְ�, ��ֶ������Ѱſ� �� ���� ���Ѻ��͸� ĳ������ġ�� ���Ѱ� end�� �Ѵ�
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), LandPredictionValue));

	if (MyPlayer->GetVelocity().Z < 0) //�������� ���� ���� ����Ʈ���̽� �߻�
	{
		if (ZipToPointAnim == EZipToPointState::FlyForward) return;
		Start = MyPlayer->GetActorLocation();

		float ZVelocity = FMath::Clamp(MyPlayer->GetCharacterMovement()->Velocity.Z, -4000, -200);
		float MulValue = UKismetMathLibrary::MapRangeClamped(MyPlayer->GetCharacterMovement()->Velocity.Z, 0, -4000, 50, 2000);
		//�������� �ӵ��� ����ؼ� ���� �� �� �Ʒ��� �����ϵ�, �ִ밪�� ������
		
		FVector SecondVector = FVector(MyPlayer->GetCharacterMovement()->Velocity.X, MyPlayer->GetCharacterMovement()->Velocity.Y, ZVelocity).GetSafeNormal() * MulValue;
		End = Start + SecondVector;

		FHitResult HitResult;
		TArray<AActor*> IgnoreActors;


		if (UKismetSystemLibrary::CapsuleTraceSingle(GetWorld(), Start, End, 20.f, 40.f, UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
			IgnoreActors, EDrawDebugTrace::None, HitResult, true))
		{
			if ((HitResult.ImpactNormal - FVector(0, 0, 1)).Size() < 1.0) //�̰� 1���� �۴ٴ°� ��簡 �ϸ��ϴٴ°Ŵϱ� ������ �ٴ���
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
