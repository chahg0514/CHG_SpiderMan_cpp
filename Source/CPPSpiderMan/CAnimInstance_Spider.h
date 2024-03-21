// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CSpiderManPlayer.h"
#include "CAnimInstance_Spider.generated.h"

UENUM(BlueprintType) //열거형을 언리얼에 등록 및 블루프린트 사용 가능
enum class ESwingType : uint8
{
	//열거형은 정의할 때 변수 이름 앞에 E를 붙인다
	//uint8: 양의 정수형 8bit
	//열거형에 uint8을 사용한다는 의미
	//열거형은 uint8만 지원한다.
	Straight UMETA(DisplayName = "straight"),
	LeftFoot UMETA(DisplayName = "leftFoot"),
	RightFoot UMETA(DisplayName = "rightFoot"),
	LeftHand UMETA(DisplayName = "leftHand"),
	RightHand UMETA(DisplayName = "rightHand"),
	LeftHandSpin UMETA(DisplayName = "leftHandSpin"),
	RightHandSpin UMETA(DisplayName = "rightHandSpin"),
	LeftHandPull UMETA(DisplayName = "leftHandPull"),
	RightHandPull UMETA(DisplayName = "rightHandPull"),


	//DisplayName: 외부에서 보여질 이름
	//c++에선 대문자로 쓰고, 블루프린트에선 소문자로 씀. 정답은 아님 그냥 블루프린트에서도 대문자로 해도 되고 c++에서 소문자로 해도 문법이상은 아님

};
/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API UCAnimInstance_Spider : public UAnimInstance
{
	GENERATED_BODY()
public:
	UCAnimInstance_Spider();
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		float Speed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		bool isMoving = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		bool isAir = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		bool isWallRunning = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		bool isWebSwinging = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		bool isLeftShift = false;
	

	void SetAimOffsetValue();
	
	//MSB3073 private access 꺼보기
public: //다른 클래스에서 바꿔야 하는 변수

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isHighJumpReadyAnim = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isWallJump = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isFreezeFallSpeed = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isSwingToLeftAnim;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isJumpFromSwing;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		bool Perch = false; //끝부분에 앉아있는지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isAttaking = false;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		float LandPredictionValue = 0.f;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		float FallSpeed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		float LateralMovementSpeedAnim = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		float Direction = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		float SwingAngleAnim = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		float Roll = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		float Pitch = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		float Yaw = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = true))
		class ACSpiderManPlayer* MyPlayer;

	FVector Start, End;
	


public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		class ACLandPredictionCurve* CurveFloat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		ESwingType SwingType = ESwingType::Straight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		FRotator ZipPointAO;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		EZipToPointState ZipToPointAnim = EZipToPointState::IDLE;
	void SetFallSpeed(float DeltaTime);
	void PredictLand(float DeltaTime);

};
