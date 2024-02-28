// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "Components/TimeLineComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CSpiderManPlayer.generated.h"



UENUM(BlueprintType) //열거형을 언리얼에 등록 및 블루프린트 사용 가능
enum class ESpiderState : uint8
{
	//열거형은 정의할 때 변수 이름 앞에 E를 붙인다
	//uint8: 양의 정수형 8bit
	//열거형에 uint8을 사용한다는 의미
	//열거형은 uint8만 지원한다.
	IDLE UMETA(DisplayName = "idle"),
	Hit UMETA(DisplayName = "hit"),
	Swinging UMETA(DisplayName = "swinging"),
	WallRunning UMETA(DisplayName = "wallRunning"),
	EndWallRunning UMETA(DisplayName = "endWallRunning"),
	ZipToPoint UMETA(DisplayName = "zipToPoint"),
	Dodge UMETA(DisplayName = "dodge"),
	FlyingPunch UMETA(DisplayName = "flyingPunch"),
	Stunned UMETA(DisplayName = "flyingPunch")
	//DisplayName: 외부에서 보여질 이름
	//c++에선 대문자로 쓰고, 블루프린트에선 소문자로 씀. 정답은 아님 그냥 블루프린트에서도 대문자로 해도 되고 c++에서 소문자로 해도 문법이상은 아님

};

UENUM()
enum class EZipToPointState : uint8
{
	IDLE UMETA(DisplayName = "idle"),
	WebPullAO UMETA(DisplayName = "webPullAO"),
	FlyForward UMETA(DisplayName = "flyForward"),
	Land UMETA(DisplayName = "land"),
	Jump UMETA(DisplayName = "jump")
};

//Atomic: ���� ��¼��
USTRUCT(Atomic, BlueprintType)
struct FAttackMontage : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemData")
		FString AttackName = FString(TEXT(""));
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemData")
		class UAnimMontage* AttackMontage;

};

USTRUCT(Atomic, BlueprintType)
struct FSoundData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemData")
		FString SoundName = FString(TEXT(""));
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemData")
		class USoundWave* SoundWave;

};

USTRUCT(Atomic, BlueprintType)
struct FAttackPosition : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackPosition")
		bool LeftFoot = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackPosition")
		bool RightFoot = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackPosition")
		bool LeftHand = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackPosition")
		bool RightHand = false;

};

UCLASS()
class CPPSPIDERMAN_API ACSpiderManPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACSpiderManPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


private:
	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
		void OnStopMovementMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
		void OnDeathMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
		void OnDodgeMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class UCameraComponent* Camera;

public:

	UPROPERTY(BlueprintReadWrite, Category = "MotionWarping")
		TObjectPtr<class UMotionWarpingComponent> MotionWarpingComp;
	


	


private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> AmmoBlueprint;

	class UCAnimInstance_Spider* AnimInsRef;

	void TimelineSetting();

public:

	void SpiderJumpPress();
	void SpiderJumpRelease();

	FRotator ReturnCameraRotation();

private:
	AActor* BollActor;
	//Jump
	void CoyoteTimeJump();
	void WallRunJumpStart();
	void EndWallRunJump();

	FRotator WallJumpStartRotation;
	FRotator WallRotStart;


	void WebSwingJump();
	FVector CalculateSwingLaunchVelocity(float ForwardSpeed, float UpSpeed);
	void JumpPress();
	void AirZip();

	bool isGround;
	bool isHighJumpReady;
	float RegularGravityScale = 1.4f;

	

	void ManageRotation();
	void SetFallRate();
	float ZVelocity;
	float LateralMovementSpeed;


	//WebSwing
	void StopWebSwinging();
	void StopWebSwingingFromJump(); //�����߿� �������� �� ���� ������, �������� true

	bool isAllowNewSwing = true;
	bool ForLoopForSwingPoints(FVector& visualSwingPoint);
	FVector CalculateOptimalSwingPoint();
	FVector OptimalSwingPoint;
	FVector VisualSwingPoint;
	FVector SwingPoint;
	bool IsTheHitInFrontOfThePlayer(FVector Point); //Ʈ���̽� Hit�� �÷��̾�� ������ ���� �ִ���
	bool IsTheHitMoreThanXUnitsAboveThePlayer(FVector Point, float X);
	bool IsTheHitAtRightAngle(FVector Point);
	void SetSwingType();
	bool isSwingToLeft;
	void StartShootWebs();
	FName SwingLocationSocketName;
	void EndShootWebs();

	FVector FindSwingForce();
	FVector SwingArcForceFormula(float VelocityClampMin, float VelocityClampMax, float ReduceForceByFactorOfX);
	void CalculateSwingSideAngle(float& returnValueRoll, float& returnValuePich);
	float SwingAngle = 0;
	float LandPredictionValue;
	float CalculateSwingAngle();



	/*UPROPERTY()
	TObjectPtr<ACWebToSwing> WebToSwing;*/
	//class ACWebToSwing* WebToSwing;

	//ZipPointUI
	void ZipEnvironmentTick();
	void ZipEnvironmentTickStart();
	void ZipEnvironmentTickEnd();
	bool isZipPointTrace = true;
	float ZipToRange = 4000.f;
	float ZipWidgetInterpSpeed = 30;
	FVector BestZipPoint;
	FVector AdjustedZipPoint;

	FVector ZipToPointLastTick;
	FVector2D ZipScreenPoint;


	void ZipPointTrace();
	bool isFoundValidZipPoint = false;

	bool TheTraces();
	float DetectionRange = 1200.f;
	bool Trace1FromCharacter(FVector& hitLocation1, FVector& hitNormal1);
	FVector HitLocation1;
	FVector HitNormal1;

	bool Trace2FromAboveFirstHit(FVector PreviousHitLocation, FVector PreviousHitNormal, FVector& hitLocation2);
	FVector HitLocation2;

	bool IsHitNotInsideObject1(FVector InputPin, FVector InputPin2);
	bool Trace3FromInFrontOfTheHit(FVector PreviousHitLocation, FVector PreviousHitNormal, FVector& hitLocation3, FVector& hitNormal3, FVector& traceDirectionVector3);
	FVector HitLocation3;
	FVector HitNormal3;
	FVector TraceDirectionVector3;

	bool IsHitNotInsideObject2(FVector A, FVector B);
	bool Trace4FromAboveTheThirdHit(FVector PreviousHitLocation, FVector PreviousHitNormal, FVector PreviousTraceDirectionVector, FVector& hitLocation4);
	FVector HitLocation4;
	bool ProjectCapsuleToZipPoint(FVector HitLocation);

	void OpenZipWidget();
	void CloseZipWidget();
	void ZipPointWidgetTick();

	//ZipPointMovement
	void ZipBeginBeforeMovement();
	void InitialRotationTowardZipPoint();
	bool isPerch = false;
	FRotator ZipBeginRotation;
	FVector ZipStartLocation;

	float CalculateZipToTimelineSpeed();

	void ZipLaunchWindow();
	float ZipJumpDelayTime; //첫번째 ZipLaunch true하는 delaytime은 이거 반으로 쪼개서 사용하기
	void DelayFinished(float delay);

	void ZipLaunch();


	void DestroyWebs();
	class AEmitter* RightHandWeb;
	class AEmitter* LeftHandWeb;
	FName RightHandSocket = "RightHandWebSocket";
	FName LeftHandSocket = "LeftHandWebSocket";
	AEmitter* SpawnWebBlueprintZip(FName name);


	void FreezeInAir();
	void UnfreezeMovement();
	FVector ZipFreezeVector;
	


public:
	//ZipPointMovementNotify
	void FlyForward();
	void ShootWebs();
	void StopShootingWebs();

	class AEmitter* WebToSwing2;
	


	AEmitter* abcd;
private:

	//WallRunPrivate
	void WallRunningTrace();
	void SetWallRunGravityAndCameraLag();
	bool WRTrueGravity = false;
	bool WRFalseGravity = false;
	bool WallRunVelocityTrace(FHitResult& hitResult, const float VelocityScalar, const float MinimumTraceDistance, const float MaximumTraceDistance);
	bool WallRunDownwards(FHitResult& hitResult, const float Length);
	bool WallRunSecondTrace(FHitResult& hitResult);
	void SetUpWallTransitionTimeLine(float Sprinting, float Walking, float Swinging, FVector TargetLocation);
	FRotator TransitionStartRot;
	FRotator TransitionEndRot;
	FVector TransitionStartLoc;
	FVector TransitionEndLoc;
	FVector FootStartLoc;
	FVector WallRunForwardVector;
	FVector WallRunRightVector;
	FRotator WallUpRotation;
	FVector WRUpSpeed; //animation
	FVector WRRightSpeed;
	void WallRunGate2(); //캐릭터의 진행방향쪽으로 Trace (현재 진행방향에 있는 벽의 경사를 파악하기 위해)
	void OpenGate2();
	void CloseGate2();
	void WallRunGate3(); //캐릭터의 아래쪽으로 Trace (아래에 벽이 없을 때 WallRunning 끝내기 위해, Gate2는 감지가 안되지만 아래쪽으로 경사가 내려가는 경우를 위해)
	void OpenGate3();
	void CloseGate3();
	bool IsOpenGate2 = false;
	bool IsOpenGate3 = false;
	FVector FindSecondWallTraceEnd();
	FRotator FindWallRunRotation();
	float WallRunVelocityDirectionLimit = 0.01;
	FVector WallRunConstantVelocityDirection;
	FRotator FindWallTransitionRotation();
	FVector CalculateWallRunDownwardsForce();


//ComboAttack

private:

	UPROPERTY(EditAnywhere, Category = "MontageData")
		class UDataTable* ComboAttackMontageDT;
	UPROPERTY(EditAnywhere, Category = "MontageData")
		class UDataTable* SoundDT;
	UPROPERTY(EditAnywhere, Category = "MontageData")
		class UDataTable* SkillAttackMontageDT;
	TArray<FName> MontageListIndex;
	UPROPERTY(EditAnywhere, Category = "MontageData")
		struct FDataTableRowHandle MontageRowHandle;

	

	int ComboCount = 0;
	int MaxComboCount = 3;
	void CheckComboAttackStart();
	void PlayNextCombo();
	void PlayComboAttackMontage(int comboCount);
	void WhenAttackFunc();

	//Get Target In Tick
	void TraceTarget();
	
	TArray<class ACEnemy_Parent*> Targets;
	
	class ACBoss_CatWoman* CurrentTarget;
	ACharacter* CharTarget;
	float TargetRange = 2500;
	

//SkillAttack
private:
	float PlayWarpSkillMontage(FName name); //이름으로 모션워핑 사용하는 몽타주 실행,  AttackMontageEnd 함수 연결, 현재 재생되는 몽타주 이름 저장했다가 끝날 때 WarpTarget 초기화, 재생시간 반환
	float PlayEndedFuncMontage(FName name); //Ended 함수 연결된 몽타주 실행
	float PlayDeathMontage(FName name);
	bool PlayMontageByName(FName name);

//Dodge

private:
	void Dodge_PlayMontage();
	void Dodge_SetVelocity(float value);
	float EvadeRange = 500;
	FVector DodgeVector;
//Collision

	void SetIgnorePawn();
	void SetBlockPawn();

	void PlaySoundByName(FName name);

public:
	bool isEnableNextCombo = false;
	
	void EndCombo();

	//Damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", Meta = (AllowPrivateAccess = true))
		ESpiderState SpiderState = ESpiderState::IDLE;
	
	//Implement In Controller, Notify Class
public:
		
	//TestMontage
	void TestMontageInput();

	//WallRunPublic
	FVector FindWallRunForwardVector();
	FVector FindWallRunRightVector();

	//WebSwinging
	void StartTryingToSwing();
	void StopTryingToSwing();

	//ZipPoint
	void ZipToPoint();
	void StopPerch();

	//Attack
	void BasicAttack();
	void ObjectAttack();
	void StopWhenAttack(float time);
	void EnableAttackCollision(FAttackPosition attackPosition);
	void DisableAttackCollision();

	void SpawnActorInSpider(FVector Location);
	void FlyingAttackInput();

	void ApplyDamage_FlyingPunch();

	//Dodge
	void DodgeInput();

	//MotionWarping
	void SetMotionWarpingLoc();

	//Hit
	void EndHitState();
	void StunLaunch();
	FVector StunNormalVec;

	UFUNCTION(BlueprintCallable)
		void SetMW_FlyingPunch();
	FString CurrentMontageName;

	UFUNCTION(BlueprintCallable)
	void SetMovementMode(EMovementMode movementMode);

	



public:

	FTimeline WallRotTimeline;
	FTimeline RotToWallTimeline;
	FTimeline RotBackTimeline;
	FTimeline WebSwingTimeline;
	FTimeline SwingForceTimeline;
	FTimeline WebSourceTimeline;
	FTimeline RotationToZipTimeline;
	UTimelineComponent* ZipLaunchTimeline;
	FTimeline FreezeTimeline;
	FTimeline DodgeTimeline;

	UCurveFloat* WRTCurveFloat;
	UCurveFloat* RotToWallUpCurveFloat;
	UCurveFloat* RotBackCurveFloat;
	UCurveFloat* WebSwingCurveFloat;
	UCurveFloat* ZipLaunchSpeedCurveFloat;
	UCurveFloat* ZipLaunchUpVectorCurveFloat;
	UCurveFloat* ZipSpeedCurve; //타임라인에 쓰는게 아니라 a값에 따른 b값을 불러오기 위해
	UCurveFloat* DodgeCurve;

	UFUNCTION()
		void WRTUpdate(float Alpha); //Gate2에서 진행한
	UFUNCTION()
		void WRTFinished();
	UFUNCTION()
		void RotToWallUpUpdate(float Alpha);
	UFUNCTION()
		void RotToWallUpFinished();
	UFUNCTION()
		void RotBackUpdate(float Alpha);
	UFUNCTION()
		void RotBackFinished();
	UFUNCTION()
		void WebSwingUpdate(float Alpha);
	UFUNCTION()
		void WebSwingFinished();
	UFUNCTION()
		void SwingForceUpdate(float Alpha);
	UFUNCTION()
		void SwingForceFinished();
	UFUNCTION()
		void WebSourceUpdate(float Alpha);
	UFUNCTION()
		void WebSourceFinished();
	UFUNCTION()
		void RotationToZipUpdate(float Alpha);
	UFUNCTION()
		void RotationToZipFinished();
	UFUNCTION()
		void ZipLaunchUpdate();
	UFUNCTION()
		void ZipLaunchFinished();

	void ZipLaunchUpdateMulti(float Value1, float Value2);

	UFUNCTION()
		void FreezeUpdate();
	UFUNCTION()
		void FreezeFinished();
	UFUNCTION()
		void DodgeUpdate(float Alpha);
	UFUNCTION()
		void DodgeFinished();

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget> ZipPointWidgetClass;
	UPROPERTY()
		class UUserWidget* ZipPointWidget;
	UPROPERTY(VisibleAnywhere, Category = "Zip")
		class UAnimMontage* ZipStartMontage;
	UPROPERTY(VisibleAnywhere, Category = "Zip")
		class UAnimMontage* AirZipMontage;
	UPROPERTY(VisibleAnywhere, Category = "Attack")
		class UAnimMontage* BasicAttack1;

	//Collision Event Delegate
	UFUNCTION()
		void OnFootAttackHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal,
		FVector NormalImpulse, const FHitResult& Hit) override;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = true))
		TSubclassOf<class UUserWidget> WidgetClass;

	class UCWidget_Spider* SpiderWidget;

	float MaxHP = 1000;
	float CurrentHP = 1000;


private:
	//State
	bool isAttack = false;
	bool isLeftShift = false;
	bool isNextAttack = false;
	bool isCanSwing = false;
	bool isWebSwinging = false;
	bool isWallRunning = false;
	bool isRotationLocked = false;
	bool isMovementLocked = false;
	bool isCanZip = false;
	bool isCanZipPointUI = false;
	bool isZipJumpWindow = false;
	bool isCanZipJump = false;
	bool isAttaking = false;
	UPROPERTY(EditAnywhere, Category = "Enemy")
	bool isBossInRange = false;


	FVector WallRunStart, WallRunEnd;
	FVector WallHitLoc, WallNormal, WallHitLoc2;

	void CustomDelay(float delayTime);
	FTimerHandle GravityTimerHandle;

	//BlueprintActor Spawn
	UObject* BollBPActor;
	UBlueprint* BollBP;

	UObject* WebToSwingActor;
	UBlueprint* WebToSwingBP;

	UObject* WebZipActor;
	UBlueprint* WebZipBP;

	//AttackCollision
	UPROPERTY(EditAnywhere, Category = "Animation")
		UCapsuleComponent* leftFootAttackCollision;
	UPROPERTY(EditAnywhere, Category = "Animation")
		UCapsuleComponent* rightFootAttackCollision;
	UPROPERTY(EditAnywhere, Category = "Animation")
		UCapsuleComponent* leftHandAttackCollision;
	UPROPERTY(EditAnywhere, Category = "Animation")
		UCapsuleComponent* rightHandAttackCollision; 


	

public:
	FORCEINLINE bool GetIsMovable() { return !isMovementLocked; }
	FORCEINLINE bool GetIsWallRunning() { return isWallRunning; }
	FORCEINLINE bool GetIsWebSwinging() { return isWebSwinging; }
	FORCEINLINE float GetSwingAngle() { return SwingAngle; }
	FORCEINLINE float GetLateralMovementSpeed() { return LateralMovementSpeed; }
	FORCEINLINE bool GetIsLeftShift() { return isLeftShift; }
	FORCEINLINE void SetIsLeftShift(bool InIsLeftShift)
	{
		isLeftShift = InIsLeftShift;
	}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetIsMovementLocked(bool InIsMovement)
	{
		isMovementLocked = InIsMovement;
	}
	FORCEINLINE void SetIsCanZipPointUI()
	{
		isCanZipPointUI = !isCanZipPointUI;
	}
};
