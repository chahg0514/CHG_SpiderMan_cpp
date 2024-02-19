// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CSpiderManPlayer.h"
#include "CAnimInstance_Spider.generated.h"

UENUM(BlueprintType) //�������� �𸮾� ��� �� �������Ʈ ��� ����
enum class ESwingType : uint8
{
	//�������� ������ �� ���� �̸� �տ� E�� ���δ�
	//uint8: ���� ������ 8bit
	//�������� uint8�� ����Ѵٴ� �ǹ�
	//�������� uint8�� �����Ѵ�.
	Straight UMETA(DisplayName = "straight"),
	LeftFoot UMETA(DisplayName = "leftFoot"),
	RightFoot UMETA(DisplayName = "rightFoot"),
	LeftHand UMETA(DisplayName = "leftHand"),
	RightHand UMETA(DisplayName = "rightHand"),
	LeftHandSpin UMETA(DisplayName = "leftHandSpin"),
	RightHandSpin UMETA(DisplayName = "rightHandSpin"),
	LeftHandPull UMETA(DisplayName = "leftHandPull"),
	RightHandPull UMETA(DisplayName = "rightHandPull"),


	//DisplayName: �ܺο��� ������ �̸�
	//c++���� �빮�ڷ� ����, �������Ʈ���� �ҹ��ڷ� ��. ������ �ƴ� �׳� �������Ʈ������ �빮�ڷ� �ص� �ǰ� c++���� �ҹ��ڷ� �ص� �����̻��� �ƴ�

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
	

public: //�ٸ� Ŭ�������� �ٲ�� �ϴ� ����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		bool isHighJumpReadyAnim = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		bool isWallJump = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		bool isFreezeFallSpeed = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		bool isSwingToLeftAnim;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		bool isJumpFromSwing;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		bool Perch = false; //���κп� �ɾ��ִ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		ESwingType SwingType = ESwingType::Straight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		FRotator ZipPointAO;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		EZipToPointState ZipToPointAnim = EZipToPointState::IDLE;
	void SetFallSpeed(float DeltaTime);
	void PredictLand(float DeltaTime);

};
