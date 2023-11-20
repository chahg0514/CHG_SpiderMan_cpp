 // Fill out your copyright notice in the Description page of Project Settings.


#include "CSpiderManPlayer.h"

#include "Engine/DamageEvents.h"

#include "CAnimInstance_Spider.h"
#include "CAttackMontage_Spider.h"
#include "CEnemy_Parent.h"
#include "CBoss_Parent.h"
#include "CBoss_CatWoman.h"
#include "DataTableName.h"

//#include "CDamageType_FlyingPunch.h"

#include "PlayMontageCallbackProxy.h"

#include "Sound/SoundWave.h"
#include "MotionWarpingComponent.h"
#include "GameFramework/Controller.h"
#include "Components/TimeLineComponent.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Components/SphereComponent.h"
#include "Containers/Array.h"

//#include "CWebToSwing.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ACSpiderManPlayer::ACSpiderManPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ZipLaunchTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("ZipLaunchTimeline"));

	static ConstructorHelpers::FClassFinder<UUserWidget> ZipPointWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Character/Widget/Web_Hud.Web_Hud_C'"));
	if (ZipPointWidgetAsset.Succeeded())
	{
		ZipPointWidgetClass = ZipPointWidgetAsset.Class;
	}

	BollBPActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Boll.Boll'")));
	if (BollBPActor)
	{

		BollBP = Cast<UBlueprint>(BollBPActor);
	}

	WebToSwingActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Script/Engine.Blueprint'/Game/Character/VFX/WebSwing_BP.WebSwing_BP'")));
	if (WebToSwingActor)
	{
		WebToSwingBP = Cast<UBlueprint>(WebToSwingActor);

	}

	WebZipActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Script/Engine.Blueprint'/Game/Character/VFX/WebZip_BP.WebZip_BP'")));
	if (WebZipActor)
	{
		WebZipBP = Cast<UBlueprint>(WebZipActor);
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DataAsset(TEXT("/Script/Engine.DataTable'/Game/Character/Data/DT_AttackMontage_Spider.DT_AttackMontage_Spider'"));
	if (DataAsset.Succeeded())
	{
		ComboAttackMontageDT = DataAsset.Object;
		MontageRowHandle.DataTable = DataAsset.Object;
		MontageRowHandle.RowName = AttackMontageName::combo1;
		MontageListIndex = ComboAttackMontageDT->GetRowNames();
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> DataAsset1(TEXT("/Script/Engine.DataTable'/Game/Character/Data/DT_SoundData_Spider.DT_SoundData_Spider'"));
	if (DataAsset1.Succeeded())
	{
		SoundDT = DataAsset1.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DataAsset2(TEXT("/Script/Engine.DataTable'/Game/Character/Data/DT_SkillAttackMontage_Spider.DT_SkillAttackMontage_Spider'"));
	if (DataAsset2.Succeeded())
	{
		SkillAttackMontageDT = DataAsset2.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ZipStartMtg(TEXT("/Script/Engine.AnimMontage'/Game/Character/CPPMontage/M_ZipPull_F.M_ZipPull_F'"));
	if (ZipStartMtg.Succeeded())
	{
		ZipStartMontage = ZipStartMtg.Object;
		
	}
	/*static ConstructorHelpers::FObjectFinder<UAnimMontage> BasicAttack1Mtg(TEXT("/Script/Engine.AnimMontage'/Game/Character/Animation/NewSkill/Backflip_Anim_Montage.Backflip_Anim_Montage'"));
	if (BasicAttack1Mtg.Succeeded())
	{
		BasicAttack1 = BasicAttack1Mtg.Object;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Success!!"));

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Fail!!"));

	}*/

	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveAsset(TEXT("/Script/Engine.CurveFloat'/Game/Blueprint/Curve_WallRun.Curve_WallRun'"));
	if (CurveAsset.Succeeded())
	{
		WRTCurveFloat = (UCurveFloat*)CurveAsset.Object;
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveAsset1(TEXT("/Script/Engine.CurveFloat'/Game/Blueprint/RotToWallUpDirection.RotToWallUpDirection'"));
	if (CurveAsset1.Succeeded())
	{
		RotToWallUpCurveFloat = (UCurveFloat*)CurveAsset1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveAsset2(TEXT("/Script/Engine.CurveFloat'/Game/Blueprint/RotBackToNormal.RotBackToNormal'"));
	if (CurveAsset2.Succeeded())
	{
		RotBackCurveFloat = (UCurveFloat*)CurveAsset.Object;
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveAsset3(TEXT("/Script/Engine.CurveFloat'/Game/Blueprint/WebSwing.WebSwing'"));
	if (CurveAsset3.Succeeded())
	{
		WebSwingCurveFloat = (UCurveFloat*)CurveAsset3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveAsset4(TEXT("/Script/Engine.CurveFloat'/Game/Blueprint/ZipLaunchSpeed.ZipLaunchSpeed'"));
	if (CurveAsset4.Succeeded())
	{
		ZipLaunchSpeedCurveFloat = (UCurveFloat*)CurveAsset4.Object;
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveAsset5(TEXT("/Script/Engine.CurveFloat'/Game/Blueprint/ZipLaunchUpVector.ZipLaunchUpVector'"));
	if (CurveAsset5.Succeeded())
	{
		ZipLaunchUpVectorCurveFloat = (UCurveFloat*)CurveAsset5.Object;
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveAsset6(TEXT("/Script/Engine.CurveFloat'/Game/Character/Data/ZipSpeedScalar.ZipSpeedScalar'"));
	if (CurveAsset6.Succeeded())
	{
		ZipSpeedCurve = (UCurveFloat*)CurveAsset6.Object;
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveAsset7(TEXT("/Script/Engine.CurveFloat'/Game/Blueprint/Curve/Curve_Montage.Curve_Montage'"));
	if (CurveAsset7.Succeeded())
	{
		DodgeCurve = (UCurveFloat*)CurveAsset7.Object;
	}
	
	

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Character/Meshes/Spidey_Lean/LeanSpiderMan.LeanSpiderMan'"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Fired"));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Character/ABP_SpiderMan.ABP_SpiderMan_C'"));
	if (AnimAsset.Succeeded())
	{

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("GetAnim"));

		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
	}
	//OnHitEvent Delegate
	FScriptDelegate AttackEventDelegate;
	AttackEventDelegate.BindUFunction(this, FName("OnOverlapBegin"));

	GetMesh()->SetRelativeLocation(FVector(0, 0, -78));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetGenerateOverlapEvents(true);
	//GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &ACSpiderManPlayer::OnOverlapBegin);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	

	//CapsulComponent
	leftFootAttackCollision = CreateDefaultSubobject<UCapsuleComponent>(FName("LeftFootCollision"));
	leftFootAttackCollision->SetupAttachment(GetMesh(), "foot_l");
	leftFootAttackCollision->SetRelativeLocation(FVector(0, -8.8, -1.2));
	leftFootAttackCollision->SetRelativeRotation(FRotator(0, 0, -60));
	leftFootAttackCollision->SetCapsuleHalfHeight(14);
	leftFootAttackCollision->SetCapsuleRadius(4.6);
	leftFootAttackCollision->SetHiddenInGame(false);
	leftFootAttackCollision->SetCollisionProfileName(TEXT("AttackCollision"));

	leftFootAttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ACSpiderManPlayer::OnOverlapBegin);
	leftFootAttackCollision->SetGenerateOverlapEvents(false);

	//leftFootAttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);



	rightFootAttackCollision = CreateDefaultSubobject<UCapsuleComponent>(FName("RightFootCollision"));
	rightFootAttackCollision->SetupAttachment(GetMesh(), "foot_r");
	rightFootAttackCollision->SetRelativeLocation(FVector(1, -9.7, -1.8));
	rightFootAttackCollision->SetRelativeRotation(FRotator(0, 0, -60));
	rightFootAttackCollision->SetCapsuleHalfHeight(14);
	rightFootAttackCollision->SetCapsuleRadius(4.6);
	rightFootAttackCollision->SetHiddenInGame(false);
	//rightFootAttackCollision->SetNotifyRigidBodyCollision(true);
	rightFootAttackCollision->SetCollisionProfileName(TEXT("AttackCollision"));
	//rightFootAttackCollision->OnComponentBeginOverlap.Add(AttackEventDelegate);
	rightFootAttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ACSpiderManPlayer::OnOverlapBegin);
	rightFootAttackCollision->SetGenerateOverlapEvents(false);

	//rightFootAttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	

	//Camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeLocation(FVector(0, 0, 0));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	//SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	//MovementSetting
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.5f;
	GetCharacterMovement()->GravityScale = 2.7f;
	GetCharacterMovement()->BrakingDecelerationFlying = 2048;
	GetCharacterMovement()->MaxFlySpeed = 400;

	GetCapsuleComponent()->SetCapsuleRadius(28);
	GetCapsuleComponent()->SetCapsuleHalfHeight(90);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	
	
	//GetCapsuleComponent()->SetCollisionProfileName("IgnoreOnlyPawn");
	
	//GetCapsuleComponent()->ComponentTags.Add(FName(TEXT("Capsuleeee")));


	RegularGravityScale = GetCharacterMovement()->GravityScale;

	Tags.Add(FName(TEXT("Player")));

	MotionWarpingComp = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
	FMotionWarpingTarget target = {};
	target.Name = FName("BasicAttack");
	MotionWarpingComp->AddOrUpdateWarpTarget(target);
}

void ACSpiderManPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

// Called when the game starts or when spawned
void ACSpiderManPlayer::BeginPlay()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,TEXT("Settt"));
	Super::BeginPlay();

	AnimInsRef = Cast<UCAnimInstance_Spider>(GetMesh()->GetAnimInstance());
	GetCharacterMovement()->SetWalkableFloorAngle(90);
	//FActorSpawnParameters df
	TimelineSetting();
	ZipPointWidget = CreateWidget<UUserWidget>(GetWorld(), ZipPointWidgetClass);
	ZipPointWidget->AddToViewport();
	ZipPointWidget->SetVisibility(ESlateVisibility::Collapsed);

	//BollActor = GetWorld()->SpawnActor<AActor>(BollBP->GeneratedClass, FVector(0,0,0), GetActorRotation());

	leftFootAttackCollision->SetCapsuleHalfHeight(14);
	rightFootAttackCollision->SetCapsuleHalfHeight(14);

	GetMesh()->SetGenerateOverlapEvents(true);

	CustomDelay(5);
	//AnimInsRef->OnMontageEnded.AddDynamic(this, &ACSpiderManPlayer::OnAttackMontageEnded);
	


	//GetWorld()->SpawnActor<AEmitter>()
	//AEmitter* Temp123 = GetWorld()->SpawnActor<AEmitter>(FVector(0,0,0), FRotator(0,0,0));
	//Temp123->GetParticleSystemComponent()->SetBeamSourcePoint(0, GetMesh()->GetSocketLocation(SwingLocationSocketName), 0);


	//CustomTimeDilation = 0;

	//WallRotTimeline.SetPlayRate(0.2);
}

// Called every frame
void ACSpiderManPlayer::Tick(float DeltaTime)
{
	//DrawDebugLine(GetWorld(), WallHitLoc, WallHitLoc + (WallNormal * 200), FColor::Emerald);
	FString abc;
	if (GetVelocity().Size() > 0.1)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("%f"), GetVelocity().Size()));

	}
	abc = GetCharacterMovement()->GetMovementName();
	/*if (AnimInsRef->ZipToPointAnim == E
	
	
	::WebPullAO && AnimInsRef->Perch)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), "t"));

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), "f"));

	}*/

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *UEnum::GetValueAsString(SpiderState)));
	
	//*UEnum::GetValueAsName().ToString()


	
	
	TraceTarget();
	ManageRotation();
	SetFallRate();
	ZipPointTrace();
	WallRunningTrace();
	CoyoteTimeJump();

	WallRotTimeline.TickTimeline(DeltaTime);
	RotToWallTimeline.TickTimeline(DeltaTime);
	RotBackTimeline.TickTimeline(DeltaTime);
	WebSwingTimeline.TickTimeline(DeltaTime);
	SwingForceTimeline.TickTimeline(DeltaTime);
	WebSourceTimeline.TickTimeline(DeltaTime);
	RotationToZipTimeline.TickTimeline(DeltaTime);
	//ZipLaunchTimeline.TickTimeline(DeltaTime);
	FreezeTimeline.TickTimeline(DeltaTime); //TimelineComponent는 Tick에서 이걸 안해주고 바로 사용 가능
	DodgeTimeline.TickTimeline(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), GetCharacterMovement()->GravityScale));

	/*FHitResult HitResult;
	TArray<AActor*> IgnoreActors;


	if (UKismetSystemLibrary::CapsuleTraceSingle(GetWorld(), GetActorLocation(), GetActorLocation() + GetVelocity().GetSafeNormal() * 100, 10.f, 20.f,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		IgnoreActors, EDrawDebugTrace::ForDuration, HitResult, true))
	{

	}*/
	
	
	//GetCharacterMovement()->AddForce(FVector(0, 0, 200000));

}

void ACSpiderManPlayer::SetMontageEnded(FString string)
{

}

void ACSpiderManPlayer::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	MotionWarpingComp->RemoveWarpTarget(FName(*CurrentMontageName));
	SpiderState = ESpiderState::IDLE;
}

void ACSpiderManPlayer::OnAttackMontageEnded2(UAnimMontage* Montage, bool bInterrupted)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("MontageEnded2222"));
}

// Called to bind functionality to input
void ACSpiderManPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACSpiderManPlayer::TimelineSetting()
{
	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, FName("WRTUpdate"));

	FOnTimelineEvent FinishedEvent;
	FinishedEvent.BindUFunction(this, FName("WRTFinished"));

	WallRotTimeline.AddInterpFloat(WRTCurveFloat, ProgressUpdate);
	WallRotTimeline.SetTimelineFinishedFunc(FinishedEvent);
	//WallRotTimeline.SetLooping(true);
	//WallRotTimeline.Play();
	////////////
	FOnTimelineFloat ProgressUpdate1;
	ProgressUpdate1.BindUFunction(this, FName("RotToWallUpUpdate"));

	FOnTimelineEvent FinishedEvent1;
	FinishedEvent1.BindUFunction(this, FName("RotToWallUpFinished"));

	RotToWallTimeline.AddInterpFloat(RotToWallUpCurveFloat, ProgressUpdate1);
	RotToWallTimeline.SetTimelineFinishedFunc(FinishedEvent1);
	////////////////
	FOnTimelineFloat ProgressUpdate2;
	ProgressUpdate2.BindUFunction(this, FName("RotBackUpdate"));

	FOnTimelineEvent FinishedEvent2;
	FinishedEvent2.BindUFunction(this, FName("RotBackFinished"));

	RotBackTimeline.AddInterpFloat(RotBackCurveFloat, ProgressUpdate2);
	RotBackTimeline.SetTimelineFinishedFunc(FinishedEvent2);

	FOnTimelineFloat ProgressUpdate3;
	ProgressUpdate3.BindUFunction(this, FName("WebSwingUpdate"));

	FOnTimelineEvent FinishedEvent3;
	FinishedEvent3.BindUFunction(this, FName("WebSwingFinished"));

	WebSwingTimeline.AddInterpFloat(WebSwingCurveFloat, ProgressUpdate3);
	WebSwingTimeline.SetTimelineFinishedFunc(FinishedEvent3);
	WebSwingTimeline.SetLooping(true);

	FOnTimelineFloat ProgressUpdate4;
	ProgressUpdate4.BindUFunction(this, FName("SwingForceUpdate"));

	FOnTimelineEvent FinishedEvent4;
	FinishedEvent4.BindUFunction(this, FName("SwingForceFinished"));

	SwingForceTimeline.AddInterpFloat(WebSwingCurveFloat, ProgressUpdate4);
	SwingForceTimeline.SetTimelineFinishedFunc(FinishedEvent4);
	SwingForceTimeline.SetLooping(true);

	FOnTimelineFloat ProgressUpdate5;
	ProgressUpdate5.BindUFunction(this, FName("WebSourceUpdate"));

	FOnTimelineEvent FinishedEvent5;
	FinishedEvent5.BindUFunction(this, FName("WebSourceFinished"));

	WebSourceTimeline.AddInterpFloat(WebSwingCurveFloat, ProgressUpdate5);
	WebSourceTimeline.SetTimelineFinishedFunc(FinishedEvent5);
	WebSourceTimeline.SetLooping(true);

	FOnTimelineFloat ProgressUpdate6;
	ProgressUpdate6.BindUFunction(this, FName("RotationToZipUpdate"));

	FOnTimelineEvent FinishedEvent6;
	FinishedEvent6.BindUFunction(this, FName("RotationToZipFinished"));

	RotationToZipTimeline.AddInterpFloat(RotToWallUpCurveFloat, ProgressUpdate6);
	RotationToZipTimeline.SetTimelineFinishedFunc(FinishedEvent6);

	FOnTimelineFloat Empty1;
	FOnTimelineFloat Empty2;


	FOnTimelineEvent ZipLaunchTickEvent;
	FOnTimelineEvent FinishedEvent7;

	ZipLaunchTickEvent.BindUFunction(this, FName("ZipLaunchUpdate"));
	FinishedEvent7.BindUFunction(this, FName("ZipLaunchFinished"));

	ZipLaunchTimeline->AddInterpFloat(ZipLaunchSpeedCurveFloat, Empty1); //타임라인에 2개의 curve 추가, Empty1변수에 저장
	ZipLaunchTimeline->AddInterpFloat(ZipLaunchUpVectorCurveFloat, Empty2);

	ZipLaunchTimeline->SetTimelinePostUpdateFunc(ZipLaunchTickEvent);
	ZipLaunchTimeline->SetTimelineFinishedFunc(FinishedEvent7);
	

	FOnTimelineFloat ProgressUpdate8;
	ProgressUpdate8.BindUFunction(this, FName("FreezeUpdate"));

	FOnTimelineEvent FinishedEvent8;
	FinishedEvent8.BindUFunction(this, FName("FreezeFinished"));

	FreezeTimeline.AddInterpFloat(WRTCurveFloat, ProgressUpdate8);
	FreezeTimeline.SetTimelineFinishedFunc(FinishedEvent8);
	FreezeTimeline.SetLooping(true);

	//이게 컴포넌트에서 아마 커브를 저장하는 무언가, 그냥 타임라인에서는 여기다가 직접 바인딩하는데 컴포넌트에선 다른함수 사용
	//다시 찾아보니까 컴포넌트도 원래방식 사용 가능한듯?


	FOnTimelineFloat ProgressUpdate9;
	ProgressUpdate9.BindUFunction(this, FName("DodgeUpdate"));

	FOnTimelineEvent FinishedEvent9;
	FinishedEvent9.BindUFunction(this, FName("DodgeFinished"));

	DodgeTimeline.AddInterpFloat(DodgeCurve, ProgressUpdate9);
	DodgeTimeline.SetTimelineFinishedFunc(FinishedEvent9);




}

void ACSpiderManPlayer::SpiderJumpPress()
{
	if (isWallRunning)
	{
		WallRunJumpStart();
	}
	else
	{
		if (isZipJumpWindow)
		{
			isCanZipJump = true;
		}
		else
		{
			if (isWebSwinging)
			{
				WebSwingJump();
			}
			else
			{
				if (isGround)
				{
					JumpPress();
				}
				else
				{
					AirZip();
				}
			}
		}
		
	}
}

void ACSpiderManPlayer::SpiderJumpRelease()
{
	if (isGround)
	{
		if (isHighJumpReady) //스페이스바를 누를 때 쉬프트를 누르고 있었고, 스페이스 Release라면
		{
			isRotationLocked = false;
			AnimInsRef->isHighJumpReadyAnim = false;

			if (GetVelocity().Size() > 2)
			{
				LaunchCharacter(FVector(0, 0, 1200 * RegularGravityScale), false, false);
			}
			else
			{
				LaunchCharacter(FVector(0, 0, 2000 * RegularGravityScale), false, false);
			}
			isHighJumpReady = false;
			isGround = false;
			return;
			

		}
		else
		{
			isGround = false;
		}
	}
	else
	{
		isHighJumpReady = false;
		AnimInsRef->isHighJumpReadyAnim = false;

	}
}

FRotator ACSpiderManPlayer::ReturnCameraRotation()
{
	return FRotator(0, GetControlRotation().Yaw + 180, 0);
}

void ACSpiderManPlayer::CoyoteTimeJump()
{
	isGround = !GetCharacterMovement()->IsFalling();
}

void ACSpiderManPlayer::WallRunJumpStart()
{
	CloseGate2();
	CloseGate3();
	isWallRunning = false;
	SpiderState = ESpiderState::IDLE;
	AnimInsRef->isWallJump = true;

	EndWallRunJump();

}

void ACSpiderManPlayer::EndWallRunJump()
{
	SpiderState = ESpiderState::EndWallRunning;
	if ((GetActorUpVector() - FVector(0, 0, 1)).Size() > 0.5) //벽에 붙어있는 정도라면 떨어지는 애니메이션 시작, 서있는 정도라면 걷도록 변경
	{

		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
		isRotationLocked = true;
		if (UKismetMathLibrary::NotEqual_VectorVector(GetCharacterMovement()->GetLastInputVector(), FVector(0, 0, 0), 0.0001)) //움직이고 있었다면
		{
			LaunchCharacter((WallNormal * 1000) + FVector(0, 0, 1000), false, false);
			RotBackTimeline.SetPlayRate(2);
			AnimInsRef->isFreezeFallSpeed = false;
			WallRotStart = GetActorRotation();
			RotBackTimeline.PlayFromStart();


		}
		else
		{
			WallJumpStartRotation = GetActorRotation();
			RotToWallTimeline.PlayFromStart();
		}
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking); 
		SpiderState = ESpiderState::IDLE;

	}
}

void ACSpiderManPlayer::WebSwingJump()
{
	StopWebSwingingFromJump();
	if (SwingAngle > 0)
	{
		
		LaunchCharacter(CalculateSwingLaunchVelocity(50, 40), false, false);
	}
}

FVector ACSpiderManPlayer::CalculateSwingLaunchVelocity(float ForwardSpeed, float UpSpeed)
{
	FVector Temp = GetVelocity().GetSafeNormal() * (ForwardSpeed * (60 / SwingAngle));
	FVector Temp2 = FVector(0, 0, UpSpeed * UKismetMathLibrary::FClamp(SwingAngle, 5, 45));
	return 	(Temp + Temp2) / 1500 * UKismetMathLibrary::FClamp(GetVelocity().Size(), 1000, 2000);
}

void ACSpiderManPlayer::JumpPress()
{
	if (isLeftShift)
	{
		isHighJumpReady = true;
		AnimInsRef->isHighJumpReadyAnim = true;
	}
	else
	{
		Jump();
	}
}

void ACSpiderManPlayer::AirZip()
{
	FVector Temp = FVector(Camera->GetForwardVector().X, Camera->GetForwardVector().Y, 0);
	LaunchCharacter(Temp * 5000, true, true);
}

void ACSpiderManPlayer::ManageRotation()
{
	if (!isRotationLocked)
	{
		if (!isWallRunning)
		{
			FRotator OuputRotator;
			FRotator TempRotator;
			FRotator TargetRotation;
			if (GetCharacterMovement()->IsFalling())
			{
				TargetRotation = GetControlRotation(); //떨어지는 중일 때는 마우스의 방향이 Target

			}
			else
			{
				FVector VelVector = GetVelocity();
				TargetRotation = UKismetMathLibrary::MakeRotFromX(VelVector); //아닐 때는 진행방향이 Target
			}

			if (isWebSwinging) //웹 스윙 중일때와 아닐 때의 Roll과 Pitch 설정
			{
				TempRotator = GetActorRotation(); 
				OuputRotator.Roll = TempRotator.Roll;
				OuputRotator.Pitch = TempRotator.Pitch;

			}
			else
			{
				TempRotator = FMath::RInterpTo(GetActorRotation(), FRotator(0, 0, 0), GetWorld()->DeltaTimeSeconds, 18);
				OuputRotator.Roll = TempRotator.Roll;
				OuputRotator.Pitch = TempRotator.Pitch;
			}

			if (GetVelocity().Length() / GetCharacterMovement()->MaxWalkSpeed >= 0.1) //캐릭터의 움직임이 있다면 Yaw 설정해줌
			{
				TempRotator = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->DeltaTimeSeconds, GetCharacterMovement()->IsFalling() ? 1 : 12);
				OuputRotator.Yaw = TempRotator.Yaw;
			}
			else
			{
				OuputRotator.Yaw = GetActorRotation().Yaw;

			}
			//떨어지는 중에는 매우 천천히, 안떨어지는 중에는 빠르게 yaw 회전축(좌우로)회전

			SetActorRotation(OuputRotator);
		}
		else
		{
			SetActorRotation(FindWallRunRotation());

		}
	}

}

void ACSpiderManPlayer::SetFallRate()
{
	ZVelocity = GetVelocity().Z;
	LateralMovementSpeed = FVector(GetVelocity().X, GetVelocity().Y, 0).Size();
}

void ACSpiderManPlayer::StopWebSwinging()
{
	if (isWebSwinging)
	{
		AnimInsRef->isJumpFromSwing = false;
		isWebSwinging = false;
		SpiderState = ESpiderState::IDLE;
		EndShootWebs();
	}
}

void ACSpiderManPlayer::StopWebSwingingFromJump()
{
	if (isWebSwinging)
	{
		AnimInsRef->isJumpFromSwing = true;
		isWebSwinging = false;
		SpiderState = ESpiderState::IDLE;
		EndShootWebs();

	}
}

bool ACSpiderManPlayer::ForLoopForSwingPoints(FVector& visualSwingPoint)
{
	OptimalSwingPoint = CalculateOptimalSwingPoint();
	for (int i = 0; i < 15; i++)
	{
		float Radius = UKismetMathLibrary::FClamp(GetVelocity().Size() / 2, 250, 500) * i;
		TArray<AActor*> IgnoreActors;
		FHitResult HitResult;
		//GetWorld()->SpawnActor<AActor>(WebBP->GeneratedClass, OptimalSwingPoint, GetActorRotation());

		if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), OptimalSwingPoint, OptimalSwingPoint + FVector(0,0,1), Radius, UEngineTypes::ConvertToTraceType(ECC_Visibility),
			false, IgnoreActors, EDrawDebugTrace::ForOneFrame, HitResult, true))
		{
			//GetWorld()->SpawnActor<AActor>(WebBP->GeneratedClass, HitResult.ImpactPoint, GetActorRotation());

			if (IsTheHitInFrontOfThePlayer(HitResult.ImpactPoint) && IsTheHitMoreThanXUnitsAboveThePlayer(HitResult.ImpactPoint, 500) 
				&& IsTheHitAtRightAngle(HitResult.ImpactPoint))
			{
				//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("WebConditionTrue"));

				visualSwingPoint = HitResult.ImpactPoint;
				return true;

			}

			
		}
	}
	return false;
}

FVector ACSpiderManPlayer::CalculateOptimalSwingPoint()
{
	FVector Temp, Temp1, Temp2;
	float TempFloat;
	Temp = GetActorLocation();
	Temp1 = Camera->GetForwardVector() * UKismetMathLibrary::FClamp(FVector(0, 0, GetVelocity().Z).Size(), 500, 3000);
	TempFloat = UKismetMathLibrary::FClamp((FVector(GetVelocity().X, GetVelocity().Y, 0).Size()) * 2.f, 500, 3000);

	Temp2 = FVector(0, 0, TempFloat);

	return Temp + Temp1 + Temp2;
	
}

bool ACSpiderManPlayer::IsTheHitInFrontOfThePlayer(FVector Point)
{
	FVector Temp1, Temp2;
	Temp1 = (Point - GetActorLocation()).GetSafeNormal();
	Temp2 = Camera->GetForwardVector();
	float Dot = UKismetMathLibrary::DotProduct2D(FVector2D(Temp1.X, Temp1.Y), FVector2D(Temp2.X, Temp2.Y));
	if (Dot > 0)
	{
		return true;
	}
	else
	{
		float Dis = (FVector(Point.X, Point.Y, 0) - FVector(GetActorLocation().X, GetActorLocation().Y, 0)).Size();
		if (Dis < 550)
		{
			return true;
		}
	}
	//Temp = UKismetMathLibrary::FindClosestPointOnLine(FVector(Point.X,Point.Y,0), FVector(GetActorLocation().X, GetActorLocation().Y,0), Camera->GetRightVector())

	return false;
}

bool ACSpiderManPlayer::IsTheHitMoreThanXUnitsAboveThePlayer(FVector Point, float X)
{
	if (Point.Z > GetActorLocation().Z + X)
	{
		return true;
	}
	return false;
}

bool ACSpiderManPlayer::IsTheHitAtRightAngle(FVector Point)
{
	FVector LeftDir = FVector::CrossProduct((Point - GetActorLocation()).GetSafeNormal(), GetVelocity().GetSafeNormal());
	FRotator Rot = UKismetMathLibrary::MakeRotFromZY((Point - GetActorLocation()).GetSafeNormal(), LeftDir * -1);
	if (Rot.Roll > 60 || Rot.Roll < -60 || Rot.Pitch > 60 || Rot.Pitch < -60)
	{
		return false;
	}
	
	return true;
}

void ACSpiderManPlayer::SetSwingType()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SetSwingType"));

	ESwingType TempSwingType;
	FVector Temp;
	Temp = FVector::CrossProduct(GetVelocity().GetSafeNormal(), (VisualSwingPoint - GetActorLocation()).GetSafeNormal()) * -1;
	FRotator ZYRot = UKismetMathLibrary::MakeRotFromZY(Temp, Temp);
	if (ZYRot.Roll > 12)
	{
		TempSwingType = ESwingType::LeftFoot;
	}
	else if (ZYRot.Roll < -12)
	{
		TempSwingType = ESwingType::RightFoot;
	}
	else
	{
		TempSwingType = ESwingType::Straight;
	}
	AnimInsRef->SwingType = TempSwingType;

	isSwingToLeft = (ZYRot.Roll > 0);
	AnimInsRef->isSwingToLeftAnim = isSwingToLeft;

	
}

void ACSpiderManPlayer::StartShootWebs()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("StartShootWebs"));

	if (isSwingToLeft)
	{
		SwingLocationSocketName = "LeftHandWebSocket";
	}
	else
	{
		SwingLocationSocketName = "RightHandWebSocket";
	}
	FTransform Temp = FTransform(FRotator(0,0,0), GetMesh()->GetSocketLocation(SwingLocationSocketName), FVector(1,1,1));
	//WebToSwing2 = 
	WebToSwing2 = Cast<AEmitter>(GetWorld()->SpawnActor<AActor>(WebToSwingBP->GeneratedClass, GetActorLocation(), GetActorRotation()));
	WebToSwing2->GetParticleSystemComponent()->SetBeamTargetPoint(0, VisualSwingPoint, 0);

	//WebToSwing = GetWorld()->SpawnActorDeferred<ACWebToSwing>(ACWebToSwing::StaticClass(), Temp);
	/*WebToSwing->Target = VisualSwingPoint;
	WebToSwing->Source = Temp.GetLocation();
	WebToSwing->FinishSpawning(Temp);*/

	WebSourceTimeline.Play();

	
	//WebToSwing->iswhat
}

void ACSpiderManPlayer::EndShootWebs()
{
	WebSourceTimeline.Stop();
	if (WebToSwing2)
	{
		WebToSwing2->Destroy();
	}
	SwingForceTimeline.Stop();
}

FVector ACSpiderManPlayer::FindSwingForce()
{
	FVector Temp, Temp1, Temp2, Temp3;

	
	float ZVelocity2 = FMath::Clamp(GetVelocity().Z, -4000, -200);
	float MulValue = UKismetMathLibrary::MapRangeClamped(GetVelocity().Z, 0, -4000, 50, 1000);
	//떨어지는 속도에 비례해서 점점 더 먼 아래를 감지하되, 최대값은 정해줌

	FVector SecondVector = FVector(GetVelocity().X, GetVelocity().Y, ZVelocity2).GetSafeNormal() * MulValue;
	FVector StartTest = GetActorLocation();
	FVector EndTest = StartTest + SecondVector;
	FHitResult HitResult;
	TArray<AActor*> IgnoreActors;

	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), StartTest, EndTest, UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		IgnoreActors, EDrawDebugTrace::None, HitResult, true))
	{
		StopWebSwinging();
		//Temp3 = FVector(0, 0, 10000);
	}
	


	//Temp
	float X = UKismetMathLibrary::Clamp((GetActorLocation() - SwingPoint).Size() / 8000, 1, 4);
	Temp = SwingArcForceFormula(400, 1800, X);

	//Temp1
	if ((SwingAngle > -10) && (SwingAngle < 30))
	{
		Temp1 = GetVelocity().GetSafeNormal() * 100;
	}
	else
	{
		Temp1 = FVector(0, 0, 0);
	}

	//Temp2
	Temp2 = FVector(Camera->GetForwardVector().X, Camera->GetForwardVector().Y, 0).GetSafeNormal() * 80000;

	
	//+Temp1 +  + Temp3
	return Temp + Temp2;
}

FVector ACSpiderManPlayer::SwingArcForceFormula(float VelocityClampMin, float VelocityClampMax, float ReduceForceByFactorOfX)
{

	FVector Temp = UKismetMathLibrary::ClampVectorSize(GetVelocity(), VelocityClampMin, VelocityClampMax);
	FVector Temp2 = (GetActorLocation() - SwingPoint).GetSafeNormal();


	FVector Temp3 = ((Temp2 * FVector::DotProduct(Temp, Temp2)) * -2) / ReduceForceByFactorOfX;
	return Temp3 * 1000;

}

void ACSpiderManPlayer::CalculateSwingSideAngle(float& returnValueRoll, float& returnValuePich)
{
	FVector Temp, Temp1;
	FRotator Result;
	Temp = (VisualSwingPoint - GetActorLocation()).GetSafeNormal();
	Temp1 = FVector::CrossProduct(Temp, GetVelocity().GetSafeNormal());
	Result = UKismetMathLibrary::MakeRotFromXZ(GetVelocity().GetSafeNormal(), Temp);
	returnValueRoll = Result.Roll;
	returnValuePich = Result.Pitch;

}

float ACSpiderManPlayer::CalculateSwingAngle()
{
	FVector Vec, Vec1, Vec2;
	Vec = (SwingPoint - GetActorLocation()).GetSafeNormal();
	Vec1 = FVector::CrossProduct(GetVelocity().GetSafeNormal(), Vec) * -1;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), UKismetMathLibrary::MakeRotFromZX(Vec, Vec1).Roll));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), GetActorRotation().Pitch));


	return GetActorRotation().Pitch;
	
}

void ACSpiderManPlayer::ZipEnvironmentTick()
{
}

void ACSpiderManPlayer::ZipEnvironmentTickStart()
{
	isZipPointTrace = true;
}

void ACSpiderManPlayer::ZipEnvironmentTickEnd()
{
	isZipPointTrace = false;
}

void ACSpiderManPlayer::ZipPointTrace()
{
	if (TheTraces())
	{
		OpenZipWidget();

	}
	else
	{
		CloseZipWidget();
	}
	ZipPointWidgetTick();
}

bool ACSpiderManPlayer::TheTraces()
{
	if (Trace1FromCharacter(HitLocation1, HitNormal1))
	{

		if (Trace2FromAboveFirstHit(HitLocation1, HitNormal1, HitLocation2))
		{
			
			if (IsHitNotInsideObject1(HitLocation2, HitLocation1))
			{
				if (ProjectCapsuleToZipPoint(HitLocation2))
				{
					BestZipPoint = HitLocation2;
					
					return true;
				}
				
			}
			else
			{
				
				return false;
			}
		}
		else
		{

			if (Trace3FromInFrontOfTheHit(HitLocation1, HitNormal1, HitLocation3, HitNormal3, TraceDirectionVector3))
			{

				if (IsHitNotInsideObject2(HitLocation1, HitLocation3))
				{

					if (Trace4FromAboveTheThirdHit(HitLocation3, HitNormal3, TraceDirectionVector3, HitLocation4))
					{

						if (ProjectCapsuleToZipPoint(HitLocation4))
						{
							BestZipPoint = HitLocation4;

							return true;
						}
					}

				}


			}

		}
	}
	return false;

}

bool ACSpiderManPlayer::Trace1FromCharacter(FVector& hitLocation1, FVector& hitNormal1)
{
	FHitResult HitResult;
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(BollActor);
	FVector Start, End;
	Start = GetActorLocation() + FVector(0, 0, 50);
	End = Start + Camera->GetForwardVector() * ZipToRange;

	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, UEngineTypes::ConvertToTraceType(ECC_Visibility), true, IgnoreActors,
		EDrawDebugTrace::None, HitResult, true))
	{
		if (HitResult.bBlockingHit)
		{
			hitLocation1 = HitResult.Location;
			hitNormal1 = HitResult.Normal;
			//BollActor->SetActorLocation(HitResult.Location);


			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool ACSpiderManPlayer::Trace2FromAboveFirstHit(FVector PreviousHitLocation, FVector PreviousHitNormal, FVector& hitLocation2)
{
	FHitResult HitResult;
	TArray<AActor*> IgnoreActors;
	FVector Start, End;
	Start = PreviousHitLocation + FVector(0, 0, DetectionRange);
	End = PreviousHitLocation;

	if (UKismetSystemLibrary::CapsuleTraceSingle(GetWorld(), Start, End, GetCapsuleComponent()->GetScaledCapsuleRadius() - 10, GetCapsuleComponent()->GetScaledCapsuleHalfHeight(),
		UEngineTypes::ConvertToTraceType(ECC_Visibility), true, IgnoreActors, EDrawDebugTrace::None, HitResult, true))
	{
		if (HitResult.bBlockingHit)
		{
			if ((HitResult.Normal - PreviousHitNormal).Size() > 1)
			{
				hitLocation2 = HitResult.ImpactPoint;
				return true;
			}
			return false;
		}
		else
		{
			return false;
		}
	}
	/*if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, UEngineTypes::ConvertToTraceType(ECC_Visibility), true, IgnoreActors,
		EDrawDebugTrace::ForDuration, HitResult, true))
	{
		
	}*/
	return false;
}

bool ACSpiderManPlayer::IsHitNotInsideObject1(FVector InputPin, FVector InputPin2) //Trace2의 시작지점이 벽이면 안되니까 그걸 여기서 걸러줌
{
	if ((InputPin - InputPin2).Length() < DetectionRange) 
	{
		return true;
	}
	
	return false;
}

bool ACSpiderManPlayer::Trace3FromInFrontOfTheHit(FVector PreviousHitLocation, FVector PreviousHitNormal, FVector& hitLocation3, FVector& hitNormal3, FVector& traceDirectionVector3)
{
	FHitResult HitResult;
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(BollActor);
	//BollActor->SetActorLocation(PreviousHitLocation);

	FVector Start, End, Temp;
	Temp = FVector(Camera->GetForwardVector().X, Camera->GetForwardVector().Y, 0).GetSafeNormal();
	Start = PreviousHitLocation + Temp * DetectionRange;
	End = PreviousHitLocation - FVector(0, 0, 150);

	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, UEngineTypes::ConvertToTraceType(ECC_Visibility), true, IgnoreActors,
		EDrawDebugTrace::None, HitResult, true))
	{
		if (HitResult.bBlockingHit)
		{

			if ((HitResult.ImpactNormal - PreviousHitNormal).Size() > 1)
			{

				hitLocation3 = HitResult.Location;
				hitNormal3 = HitResult.Normal;
				traceDirectionVector3 = (Start - End).GetSafeNormal();
				return true;
			}
		}
		return false;
	}
	return false;
}

bool ACSpiderManPlayer::IsHitNotInsideObject2(FVector A, FVector B)
{
	if ((A - B).Size() < (DetectionRange))
	{
		return true;
	}
	return false;
}

bool ACSpiderManPlayer::Trace4FromAboveTheThirdHit(FVector PreviousHitLocation, FVector PreviousHitNormal, FVector PreviousTraceDirectionVector, FVector& hitLocation4)
{
	FHitResult HitResult;
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(BollActor);
	//BollActor->SetActorLocation(PreviousHitLocation);

	FVector Start, End, Temp;
	Start = PreviousHitLocation + FVector(0,0,DetectionRange);
	End = PreviousHitLocation;

	if (UKismetSystemLibrary::CapsuleTraceSingle(GetWorld(), Start, End, GetCapsuleComponent()->GetScaledCapsuleRadius() - 10, GetCapsuleComponent()->GetScaledCapsuleHalfHeight(),
		UEngineTypes::ConvertToTraceType(ECC_Visibility), true, IgnoreActors, EDrawDebugTrace::None, HitResult, true))
	{
		if ((HitResult.Normal - PreviousHitNormal).Size() > 1)
		{
			hitLocation4 = HitResult.ImpactPoint;
			return true;
		}
	}
	return false;
}

bool ACSpiderManPlayer::ProjectCapsuleToZipPoint(FVector HitLocation)
{
	FHitResult HitResult;
	TArray<AActor*> IgnoreActors;
	FVector Start, End;
	Start = HitLocation + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + 4);
	End = Start + FVector(0, 0, 1);
	if(UKismetSystemLibrary::CapsuleTraceSingle(GetWorld(), Start, End, GetCapsuleComponent()->GetScaledCapsuleRadius() - 10, GetCapsuleComponent()->GetScaledCapsuleHalfHeight(),
		UEngineTypes::ConvertToTraceType(ECC_Visibility), true, IgnoreActors, EDrawDebugTrace::None, HitResult, true))
	{
		return false;
	}
	return true;
}

void ACSpiderManPlayer::OpenZipWidget()
{
	ZipPointWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	isCanZip = true;

}

void ACSpiderManPlayer::CloseZipWidget()
{
	isCanZip = false;
	ZipPointWidget->SetVisibility(ESlateVisibility::Hidden);

}

void ACSpiderManPlayer::ZipPointWidgetTick()
{
	if (isCanZip)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("True242"));

		//GetWorld()->SpawnActor<AActor>(WebBP->GeneratedClass, OptimalSwingPoint, GetActorRotation());

		ZipToPointLastTick = UKismetMathLibrary::VInterpTo(ZipToPointLastTick, BestZipPoint, GetWorld()->DeltaTimeSeconds, ZipWidgetInterpSpeed);
		UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(GetWorld(), 0), ZipToPointLastTick, ZipScreenPoint, true);
		ZipPointWidget->SetPositionInViewport(ZipScreenPoint);
	}
}

void ACSpiderManPlayer::ZipBeginBeforeMovement()
{
	if (AnimInsRef->ZipToPointAnim == EZipToPointState::IDLE)
	{
		SpiderState = ESpiderState::ZipToPoint;
		ZipEnvironmentTickEnd();
		isRotationLocked = true;
		isMovementLocked = true;
		FVector ForwardTemp = FVector(Camera->GetForwardVector().X, Camera->GetForwardVector().Y, 0).GetSafeNormal();
		AdjustedZipPoint = BestZipPoint + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + 1) + (ForwardTemp * 15); 
		AnimInsRef->ZipToPointAnim = EZipToPointState::WebPullAO;
		FRotator Temp = UKismetMathLibrary::NormalizedDeltaRotator(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), BestZipPoint), GetActorRotation());
		AnimInsRef->ZipPointAO = Temp;

		PlayAnimMontage(ZipStartMontage);
		InitialRotationTowardZipPoint();
	}
}

void ACSpiderManPlayer::InitialRotationTowardZipPoint()
{
	isPerch ? CustomDelay(0.05) : CustomDelay(0.15);
	isPerch ? RotationToZipTimeline.SetPlayRate(2) : RotationToZipTimeline.SetPlayRate(1);
	ZipBeginRotation = GetActorRotation();
	RotationToZipTimeline.PlayFromStart();
	

}

float ACSpiderManPlayer::CalculateZipToTimelineSpeed()
{
	float Temp = (AdjustedZipPoint - ZipStartLocation).Size();
	float CurveFloat = ZipSpeedCurve->GetFloatValue(Temp / ZipToRange);
	float Temp2 = ZipToRange / Temp;

	return CurveFloat * Temp2;
}

void ACSpiderManPlayer::ZipLaunchWindow()
{
	float Temp = 1 / (1 / CalculateZipToTimelineSpeed() - 0.2);
	ZipJumpDelayTime /= Temp;
	isPerch = true;
	AnimInsRef->Perch = true;
	FTimerHandle ZipLaunchHandle1;
	GetWorld()->GetTimerManager().SetTimer(ZipLaunchHandle1, FTimerDelegate::CreateLambda([&]()
		{
			isZipJumpWindow = true;
			GetWorld()->GetTimerManager().ClearTimer(ZipLaunchHandle1);
		}), ZipJumpDelayTime / 2, false);
	FTimerHandle ZipLaunchHandle2;

	GetWorld()->GetTimerManager().SetTimer(ZipLaunchHandle2, FTimerDelegate::CreateLambda([&]()
		{
			isZipJumpWindow = false;
			if (isCanZipJump)
			{
				AnimInsRef->ZipToPointAnim = EZipToPointState::Jump;
			}
			else
			{
				AnimInsRef->ZipToPointAnim = EZipToPointState::Land;
				ZipEnvironmentTickStart();
			}
			GetWorld()->GetTimerManager().ClearTimer(ZipLaunchHandle2);
			DelayFinished(Temp);
		}), ZipJumpDelayTime, false);


}

void ACSpiderManPlayer::DelayFinished(float delay)
{
	FTimerHandle ZipLaunchHandle3;

	GetWorld()->GetTimerManager().SetTimer(ZipLaunchHandle3, FTimerDelegate::CreateLambda([&]()
		{
			if (isCanZipJump)
			{
				ZipLaunchTimeline->Stop();
				ZipLaunch();
				DestroyWebs();
			}

			GetWorld()->GetTimerManager().ClearTimer(ZipLaunchHandle3);
		}), 0.3 / delay, false);
}

void ACSpiderManPlayer::ZipLaunch()
{
	LaunchCharacter(GetActorForwardVector() * 2000.f + FVector(0, 0, 2000), true, true);
	isCanZipJump = false;
	isMovementLocked = false;
	isRotationLocked = false;
	isPerch = false;
	AnimInsRef->Perch = false;
	ZipEnvironmentTickStart();
}



void ACSpiderManPlayer::DestroyWebs()
{
	if (RightHandWeb)
	{
		RightHandWeb->Destroy();
		LeftHandWeb->Destroy();
	}
}

AEmitter* ACSpiderManPlayer::SpawnWebBlueprintZip(FName name)
{
	return Cast<AEmitter>(GetWorld()->SpawnActor<AActor>(WebZipBP->GeneratedClass, GetMesh()->GetSocketLocation(name), FRotator(0)));
}

void ACSpiderManPlayer::FreezeInAir()
{
	GetCharacterMovement()->StopMovementImmediately();
	ZipFreezeVector = GetActorLocation();
	FreezeTimeline.PlayFromStart();

}

void ACSpiderManPlayer::UnfreezeMovement()
{
	FreezeTimeline.Stop();
}

void ACSpiderManPlayer::FlyForward()
{
	ZipStartLocation = GetActorLocation();
	ZipLaunchTimeline->SetPlayRate(CalculateZipToTimelineSpeed());
	AnimInsRef->ZipToPointAnim = EZipToPointState::FlyForward;

	UnfreezeMovement();
	ZipLaunchTimeline->PlayFromStart();
	ZipLaunchWindow();
}

void ACSpiderManPlayer::ShootWebs()
{
	RightHandWeb = SpawnWebBlueprintZip(RightHandSocket);
	RightHandWeb->GetParticleSystemComponent()->SetBeamTargetPoint(0, BestZipPoint, 0);
	RightHandWeb->GetParticleSystemComponent()->SetBeamSourcePoint(0, GetMesh()->GetSocketLocation(RightHandSocket), 0);


	LeftHandWeb = SpawnWebBlueprintZip(LeftHandSocket);
	LeftHandWeb->GetParticleSystemComponent()->SetBeamTargetPoint(0, BestZipPoint, 0);
	LeftHandWeb->GetParticleSystemComponent()->SetBeamSourcePoint(0, GetMesh()->GetSocketLocation(LeftHandSocket), 0);

}

void ACSpiderManPlayer::StopShootingWebs()
{

}

void ACSpiderManPlayer::WallRunningTrace() //isWallRunning이 false일 때만 실행, 현재 진행 방향으로 트레이스, 바닥이면 isWallRunning 시작
{
	if (SpiderState == ESpiderState::IDLE && !isWallRunning)
	{
		if (GetVelocity().Size() > 200)
		{
			FHitResult HitResult;
			TArray<AActor*> IgnoreActors;
			
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), IsWallRunHit));


			if (WallRunVelocityTrace(HitResult, 5, 40, 200))
			{

				WallHitLoc = HitResult.ImpactPoint;
				WallNormal = HitResult.Normal;

				if ((WallNormal - FVector(0, 0, 1)).Size() > 1.0) //두개의 노멀 벡터의 차이가 1 이상이다 => 두 선의 각도가 60도 이상이다
				{

					FHitResult HitResultSecond;
					if (WallRunSecondTrace(HitResultSecond))
					{
						WallHitLoc2 = HitResult.ImpactPoint;
						StopWebSwinging();
						isWallRunning = true;
						SpiderState = ESpiderState::WallRunning;
						GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
						isRotationLocked = true;
						SetUpWallTransitionTimeLine(1.0, 0.35, 100, WallHitLoc2);
						WallRotTimeline.PlayFromStart();

						//GetCharacterMovement()->GravityScale = 0;
					}
				}
				else
				{
					//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Ground"));

				}
			}

		}
		
	}
	else if (isWallRunning)
	{
		WallRunGate3();
		WallRunGate2();
	}
	
}

void ACSpiderManPlayer::SetWallRunGravityAndCameraLag()
{
	if (isWallRunning)
	{
		if (!WRTrueGravity)
		{
			GetCharacterMovement()->GravityScale = 0;
			WRTrueGravity = true;
			WRFalseGravity = false;
		}
	}
	else
	{
		if (!WRFalseGravity)
		{
			GetCharacterMovement()->GravityScale = RegularGravityScale;
			WRFalseGravity = true;
			WRTrueGravity = false;
		}
	}
}

bool ACSpiderManPlayer::WallRunVelocityTrace(FHitResult& hitResult, const float VelocityScalar, const float MinimumTraceDistance, const float MaximumTraceDistance)
{
	FHitResult HitResult;
	TArray<AActor*> IgnoreActors;

	WallRunStart = GetActorLocation();
	WallRunEnd = WallRunStart + (FVector(GetVelocity().GetSafeNormal()).GetSafeNormal() * 150);
	
	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), WallRunStart, WallRunEnd, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, IgnoreActors,
		EDrawDebugTrace::ForOneFrame, HitResult, true,FLinearColor::Yellow, FLinearColor::White))
	{

		hitResult = HitResult;
		return true;
	}
	else
	{
		return false;

	}

}

bool ACSpiderManPlayer::WallRunDownwards(FHitResult& hitResult, const float Length)
{
	FHitResult HitResult;
	TArray<AActor*> IgnoreActors;
	FVector Start, End;

	Start = GetActorLocation();
	End = Start + (GetActorUpVector() * -1).GetSafeNormal() * Length;

	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, IgnoreActors,
		EDrawDebugTrace::ForOneFrame, HitResult, true,FColor::Green))
	{
		//DrawDebugLine(GetWorld(), HitResult.ImpactPoint, HitResult.ImpactPoint + (HitResult.Normal * 400), FColor::Yellow);

		hitResult = HitResult;


		return true;
	}
	else
	{
		return false;

	}
}

bool ACSpiderManPlayer::WallRunSecondTrace(FHitResult& hitResult)
{
	FVector Start, End;
	Start = GetActorLocation();
	End = FindSecondWallTraceEnd();

	FHitResult HitResult;
	TArray<AActor*> IgnoreActors;

	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, IgnoreActors,
		EDrawDebugTrace::None, HitResult, true))
	{
		hitResult = HitResult;
		return true;
	}
	return false;
}

void ACSpiderManPlayer::SetUpWallTransitionTimeLine(float Sprinting, float Walking, float Swinging, FVector TargetLocation) //여기서 벽타기 시작할 정확한 위치와 회전을 정해줌
{
	if (isWebSwinging)
	{
		GetCharacterMovement()->MaxAcceleration = 50000;
		WallRotTimeline.SetPlayRate(Swinging);
	}
	else
	{
		if (isLeftShift)
		{
			GetCharacterMovement()->MaxAcceleration = 50000;
			WallRotTimeline.SetPlayRate(Sprinting);

		}
		else
		{
			WallRotTimeline.SetPlayRate(Walking);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("33333333"));

		}
	}
	TransitionStartLoc = GetActorLocation();
	TransitionStartRot = GetActorRotation();

	
	FootStartLoc = GetMesh()->GetComponentLocation(); //root 위치라고 생각하면 될듯
	TransitionEndLoc = TargetLocation + (WallNormal * GetCapsuleComponent()->GetScaledCapsuleHalfHeight()); //이걸 하는 이유가 캐릭터의 기즈모가 캐릭터캡슐 절반위치이기 때문
	TransitionEndRot = FindWallTransitionRotation();
}

void ACSpiderManPlayer::WallRunGate2()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Gate2"));

	if (IsOpenGate2)
	{
		if (GetVelocity().Size() > 200)
		{
			FHitResult HitResult;
			TArray<AActor*> IgnoreActors;



			if (WallRunVelocityTrace(HitResult, 4, 100, 300))
			{
				
				if ((HitResult.Normal - FVector(0, 0, 1)).Size() > 1.0)
				{
					if ((WallNormal - HitResult.Normal).Length() > 0.35)
					{
						WallHitLoc = HitResult.ImpactPoint;
						WallNormal = HitResult.Normal;

						FHitResult HitResult2;


						if (WallRunSecondTrace(HitResult2))
						{
							WallHitLoc2 = HitResult2.ImpactPoint;
							CloseGate2();
							CloseGate3();
							isRotationLocked = true;
							SetUpWallTransitionTimeLine(1, 0.3, 0, WallHitLoc); //이걸 계속 해주면서 벽의 위쪽 벡터, 오른쪽 벡터를 구해줘야함
							WallRotTimeline.PlayFromStart();

						}
					}

				}
				else
				{
					CloseGate2();
					CloseGate3();
					GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
					SpiderState = ESpiderState::IDLE;
					isWallRunning = false;

				}
			}

		}
	}
}

void ACSpiderManPlayer::OpenGate2()
{
	FTimerHandle WaitHandle;
	float WaitTime = 1;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			IsOpenGate2 = true;


		}), WaitTime, false);

}

void ACSpiderManPlayer::CloseGate2()
{
	IsOpenGate2 = false;

}

void ACSpiderManPlayer::WallRunGate3()
{
	if (IsOpenGate3)
	{
		FHitResult hitResult;
		if (WallRunDownwards(hitResult, 500))
		{
			WallNormal = UKismetMathLibrary::VInterpTo_Constant(WallNormal, hitResult.Normal, GetWorld()->DeltaTimeSeconds, 5);

			WallHitLoc = hitResult.ImpactPoint;
			FHitResult HitResult2;
			if (WallRunSecondTrace(HitResult2))
			{
				WallHitLoc2 = HitResult2.ImpactPoint;
				GetCharacterMovement()->AddForce(CalculateWallRunDownwardsForce());
			}
			else
			{
				CloseGate2();
				CloseGate3();
				SpiderState = ESpiderState::IDLE;
				isWallRunning = false;
				AnimInsRef->isWallJump = false;

				EndWallRunJump();
			}
		}
		else
		{
			CloseGate2();
			CloseGate3();
			SpiderState = ESpiderState::IDLE;
			isWallRunning = false;
			AnimInsRef->isWallJump = false;

			EndWallRunJump();
		}
	}
}

void ACSpiderManPlayer::OpenGate3()
{
	IsOpenGate3 = true;
}

void ACSpiderManPlayer::CloseGate3()
{
	IsOpenGate3 = false;

}

FVector ACSpiderManPlayer::FindSecondWallTraceEnd()
{
	FVector Temp1, Temp2;
	Temp1 = (WallHitLoc - GetActorLocation()).GetSafeNormal();
	if (WallNormal.Z > -1.5 && WallNormal.Z < -0.5)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Slope"));

		Temp2 = GetActorForwardVector();
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("NotSlope"));

		Temp2 = FVector(0, 0, 1);

	}
	
	return GetActorLocation() + ((Temp1 + Temp2).GetSafeNormal() * 1000);
}

FRotator ACSpiderManPlayer::FindWallRunRotation()
{
	FVector Temp1, Temp2;
	if (GetVelocity().GetSafeNormal().Size() >= 0.01)
	{
		WallRunConstantVelocityDirection = FMath::VInterpConstantTo(WallRunConstantVelocityDirection, GetVelocity().GetSafeNormal(), GetWorld()->DeltaTimeSeconds, 5);
	}
	if (WallRunConstantVelocityDirection.Size() < 0.01)
	{
		Temp1 = (WallHitLoc2 - WallHitLoc).GetSafeNormal();
	}
	else
	{
		Temp1 = WallRunConstantVelocityDirection;
	}
	Temp2 = (Temp1.Cross(WallNormal) * -1).Cross(WallNormal);
	WallRunForwardVector = Temp2.GetSafeNormal();
	WallRunRightVector = WallNormal.Cross(Temp2).GetSafeNormal();
	Temp1 = (WallHitLoc2 - WallHitLoc).GetSafeNormal();
	Temp2 = (Temp1.Cross(WallNormal) * -1).Cross(WallNormal);
	WallUpRotation = UKismetMathLibrary::MakeRotationFromAxes(Temp2, Temp2.Cross(WallNormal),WallNormal);

	return UKismetMathLibrary::MakeRotationFromAxes(WallRunForwardVector, WallRunRightVector, WallNormal);
}

FRotator ACSpiderManPlayer::FindWallTransitionRotation() //현재 감지된 벽에서 위쪽, 오른쪽 벡터 구함(캐릭터가 바라보는 방향, 캐릭터의 회전과 상관 없이)
{
	FVector Cross1 = ((WallHitLoc - FootStartLoc).GetSafeNormal().Cross(WallNormal) * -1).Cross(WallNormal); //이게 그니까 벽의 경사에 따른 벽의 위쪽으로 향하는 벡터.
	WallRunForwardVector = Cross1.GetSafeNormal();
	WallRunRightVector = WallNormal.Cross(Cross1).GetSafeNormal(); //노말벡터랑 또 외적해서 오른쪽벡터 구하고
	WallUpRotation = UKismetMathLibrary::MakeRotationFromAxes(WallRunForwardVector, WallRunRightVector, WallNormal); //x축이 벽의 위쪽(Cross1)을 향하는 회전값

	return WallUpRotation;
}

FVector ACSpiderManPlayer::CalculateWallRunDownwardsForce()
{
	FVector First;
	float second;
	First = (WallNormal * -1) * (GetVelocity().Length() * 5);
	second = (((WallHitLoc - GetActorLocation()).Length()) - GetCapsuleComponent()->GetScaledCapsuleHalfHeight()) * 10;

	return First * second;
}

void ACSpiderManPlayer::CheckComboAttackStart()
{
	if (SpiderState == ESpiderState::IDLE && !GetCharacterMovement()->IsFalling()) //땅이고, 벽타거나 웹스윙중이거나 집포인트중 아닐때 (아직 집포인트 설정 안함)
	{
		if (isEnableNextCombo) //다음 콤보 실행
		{
			isEnableNextCombo = false;
			PlayNextCombo();
		}
		else
		{
			if (ComboCount == 0) //처음 공격 실행
			{
				PlayNextCombo();
			}
			//좌클릭 연타중
		}
	}
	
}

void ACSpiderManPlayer::PlayNextCombo()
{
	if (ComboCount != MaxComboCount) //마지막 콤보 실행이 아니라면
	{
		PlayAttackMontage(ComboCount);
		
		ComboCount++;
	}
	else
	{
		PlayAttackMontage(ComboCount);
		
	}
}

void ACSpiderManPlayer::PlayAttackMontage(int comboCount)
{
	FAttackMontage temp = *ComboAttackMontageDT->FindRow<FAttackMontage>(MontageListIndex[comboCount], TEXT(""));
	//SetMotionWarpingLoc();
	
	FOnMontageEnded endDelegate;
	endDelegate.BindUObject(this, &ACSpiderManPlayer::OnAttackMontageEnded2);
	
	
	//AnimInsRef->Set
	//AnimInsRef->Montage_Play(temp.AttackMontage);
	PlayAnimMontage(temp.AttackMontage);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	/*if (comboCount == 0)
	{
		AnimInsRef->Montage_SetEndDelegate(endDelegate, temp.AttackMontage);
	}*/
	
	
	isMovementLocked = true;
}

void ACSpiderManPlayer::WhenAttackFunc()
{

}

void ACSpiderManPlayer::TraceTarget() //보스가 있으면 보스 타겟으로, 없으면 타겟들중 임의로
{
	TArray<AActor*> IgnoreActors;
	TArray<FHitResult> OutHits;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	//GetWorld()->SpawnActor<AActor>(WebBP->GeneratedClass, OptimalSwingPoint, GetActorRotation());
	if(UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), GetActorLocation(), GetActorLocation() + FVector(0, 0, 1), TargetRange, ObjectTypes, false, IgnoreActors, 
		EDrawDebugTrace::None, OutHits, true))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"), OutHits.Num()));
		for (auto &i : OutHits)
		{
			if (i.GetActor()->ActorHasTag("Boss"))
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("HasTagBoss"));
				CurrentTarget = Cast<ACharacter>(i.GetActor());
				if (CurrentTarget)
				{
					isBossInRange = true;
					return;
				}
			}
			else if(i.GetActor()->ActorHasTag("Enemy"))
			{
				ACEnemy_Parent* temp = Cast<ACEnemy_Parent>(i.GetActor());
				if (temp)
				{
					Targets.AddUnique(temp);
				}

			}
			
		}
	}
	while (!CurrentTarget)
	{
		if (Targets.IsEmpty()) break;
		if (Targets[0]) //이걸 거리가 제일 가까운거로 바꾸던지 하자 일단 지금은 임시로
		{
			CurrentTarget = Targets[0];
		}
		else
		{
			Targets.RemoveAt(0);
		}
	}

}

float ACSpiderManPlayer::PlayWarpSkillMontage(FName name) 
{
	if (SkillAttackMontageDT)
	{
		UAnimMontage* montage = SkillAttackMontageDT->FindRow<FAttackMontage>(name, TEXT(""))->AttackMontage;
		if (montage)
		{
			CurrentMontageName = name.ToString();
			float temp = PlayAnimMontage(montage);

			FOnMontageEnded endDelegate;
			endDelegate.BindUObject(this, &ACSpiderManPlayer::OnAttackMontageEnded);
			AnimInsRef->Montage_SetEndDelegate(endDelegate, montage);

			return temp;
		}
	}
	return 0;
}

void ACSpiderManPlayer::Dodge_PlayMontage()//몽타주 재생, velocity 함수 실행, 방향은 일단 앞으로, curve 사용
{
	float playTime = PlayWarpSkillMontage(SkillAttackName::Dodge);
	SetIgnorePawn();
	DodgeTimeline.SetPlayRate(1 / playTime);
	DodgeTimeline.PlayFromStart();
	//콜리전 변경
}

void ACSpiderManPlayer::Dodge_SetVelocity(float value)//적 위치와 반대편으로 velocity 설정은 아니고 일단 앞쪽으로 함
{
	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, TEXT("velocity"));
	if (GetVelocity().Length() > 0)
	{
		GetCharacterMovement()->Velocity = GetVelocity().GetSafeNormal() * EvadeRange * value;
		//DodgeVector = GetVelocity().GetSafeNormal();
	}
	else
	{
		GetCharacterMovement()->Velocity = GetActorForwardVector() * EvadeRange * value;
	}
}

void ACSpiderManPlayer::SetIgnorePawn()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

void ACSpiderManPlayer::SetBlockPawn()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
}

void ACSpiderManPlayer::PlaySoundByName(FName name)
{
	if (SoundDT)
	{
		USoundWave* punchSound = SoundDT->FindRow<FSoundData>(name, TEXT(""))->SoundWave;
		if (punchSound)
		{
			UGameplayStatics::PlaySound2D(this, punchSound);
		}
	}
}

float ACSpiderManPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return Damage;
}

void ACSpiderManPlayer::EndCombo()
{
	isEnableNextCombo = false;
	ComboCount = 0;
	isMovementLocked = false;
}

//public

FVector ACSpiderManPlayer::FindWallRunForwardVector()
{
	float temp = ((UKismetMathLibrary::GetForwardVector(GetControlRotation()) - WallRunForwardVector).Length() - 0.6);
	FVector vector1, vector2;
	if ( temp > 1)
	{
		vector1 = ((temp - 1) * -1) * WallRunForwardVector;
	}
	else
	{
		vector1 = (1 - temp) * WallRunForwardVector;

	}
	temp = ((UKismetMathLibrary::GetForwardVector(GetControlRotation()) - WallRunRightVector).Length() - 0.4);
	if (temp > 1)
	{
		vector2 = ((temp - 1) * -1) * WallRunRightVector;
	}
	else
	{
		vector2 = (1 - temp) * WallRunRightVector;

	}

	return vector1 + vector2;
}

FVector ACSpiderManPlayer::FindWallRunRightVector()
{
	float temp = ((UKismetMathLibrary::GetRightVector(GetControlRotation()) - WallRunForwardVector).Length() - 0.4);
	FVector vector1, vector2;
	if (temp > 1)
	{
		vector1 = ((temp - 1) * -1) * WallRunForwardVector;
	}
	else
	{
		vector1 = (1 - temp) * WallRunForwardVector;

	}
	temp = ((UKismetMathLibrary::GetRightVector(GetControlRotation()) - WallRunRightVector).Length() - 0.4);
	if (temp > 1)
	{
		vector2 = ((temp - 1) * -1) * WallRunRightVector;
	}
	else
	{
		vector2 = (1 - temp) * WallRunRightVector;

	}
	return (vector1 + vector2).GetSafeNormal();
}

void ACSpiderManPlayer::StartTryingToSwing()
{
	WebSwingTimeline.Play();
}

void ACSpiderManPlayer::StopTryingToSwing()
{
	WebSwingTimeline.Stop();

	StopWebSwinging();
}


void ACSpiderManPlayer::ZipToPoint()
{
	if (isCanZip)
	{
		ZipBeginBeforeMovement();
	}
	//UPlayMontageCallbackProxy::PlayMontage();
	
	
}

void ACSpiderManPlayer::StopPerch()
{
	isPerch = false;
	AnimInsRef->Perch = false;
}

void ACSpiderManPlayer::BasicAttack() 
{
	CheckComboAttackStart();
}

void ACSpiderManPlayer::StopWhenAttack(float time)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("StopWhenAttack"));
	DisableAttackCollision();
	CustomTimeDilation = 0;
	FTimerHandle ZipLaunchHandle1;
	GetWorld()->GetTimerManager().SetTimer(ZipLaunchHandle1, FTimerDelegate::CreateLambda([&]()
		{
			CustomTimeDilation = 1;
			//GetMesh()->GetAnimInstance()->Montage_Stop(1);
			isMovementLocked = false;
		}), time, false);
}

void ACSpiderManPlayer::EnableAttackCollision()
{
	leftFootAttackCollision->SetGenerateOverlapEvents(true);
	rightFootAttackCollision->SetGenerateOverlapEvents(true);
}

void ACSpiderManPlayer::DisableAttackCollision()
{
	leftFootAttackCollision->SetGenerateOverlapEvents(false);
	rightFootAttackCollision->SetGenerateOverlapEvents(false);
}

void ACSpiderManPlayer::SpawnActorInSpider(FVector Location)
{
	GetWorld()->SpawnActor<AActor>(BollBP->GeneratedClass, FTransform(GetActorRotation(), Location, FVector(0.1, 0.1, 0.1)));
}

void ACSpiderManPlayer::FlyingAttackInput()
{
	if (SpiderState == ESpiderState::IDLE && !isMovementLocked && CurrentTarget) //이걸 나중에는 현재 바라보는 방향에 카운터펀치 날릴 적이 있는지 확인하는 변수로 변경
	{
		SpiderState = ESpiderState::FlyingPunch;
		PlayWarpSkillMontage(SkillAttackName::FlyingPunch);
	}
}

void ACSpiderManPlayer::ApplyDamage_FlyingPunch()
{
	FVector Start = GetActorLocation();
	FVector End = GetActorLocation() + GetActorForwardVector() * 50;
	TArray<AActor*> Ignore;
	Ignore.Add(this);
	TArray<FHitResult> OutHits;

	FHitResult hitResult;
	if (UKismetSystemLibrary::CapsuleTraceMulti(GetWorld(), Start, End, 40, 100, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), true, Ignore,
		EDrawDebugTrace::None, OutHits, true, FLinearColor::Yellow))
	{
		
		for (auto i : OutHits)
		{
			
			ACBoss_CatWoman *target = Cast<ACBoss_CatWoman>(i.GetActor());
			if (target)
			{
				FPointDamageEvent pointDamageEvent;
				FHitResult pointHitResult;
				hitResult.Location = i.Location;
				pointDamageEvent.HitInfo = pointHitResult;
				//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Result"));
				target->TakeDamage(100, pointDamageEvent, GetController(), this);
				PlaySoundByName(SoundName::Punch0);
			}
		}
		
	}
}

void ACSpiderManPlayer::DodgeInput()
{
	if (SpiderState == ESpiderState::IDLE && !isMovementLocked) //idle이고, 움직일 수 있는 상태라는건 공격중이 아니라는걸로 간주, 기본공격일 때는 isMovementLocked true이므로
	{
		SpiderState = ESpiderState::Dodge;
		Dodge_PlayMontage();
	}
}

void ACSpiderManPlayer::SetMotionWarpingLoc()
{
	FString MotionWarpingName = "Attack" + FString::FromInt(ComboCount);
	
	if (CurrentTarget)
	{
		FVector DirToSelf = (GetActorLocation() - CurrentTarget->GetActorLocation()).GetSafeNormal();
		FVector DirToTarget = CurrentTarget->GetActorLocation() - GetActorLocation();
		//GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		//캐릭터 위치랑 적 위치랑 z좌표가 다를 때(지형에 따라) 바꿔줘야함
		MotionWarpingComp->AddOrUpdateWarpTargetFromLocationAndRotation(*MotionWarpingName, CurrentTarget->GetActorLocation() + DirToSelf * 80,
			UKismetMathLibrary::MakeRotFromX(FVector(DirToTarget.X, DirToTarget.Y, 0)));
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("ImplementSet"));
	}
	
}

void ACSpiderManPlayer::SetMW_FlyingPunch()
{
	if (CurrentTarget)
	{
		FVector DirToSelf = (GetActorLocation() - CurrentTarget->GetActorLocation()).GetSafeNormal();
		FVector DirToTarget = CurrentTarget->GetActorLocation() - GetActorLocation();
		MotionWarpingComp->AddOrUpdateWarpTargetFromLocationAndRotation(SkillAttackName::FlyingPunch, CurrentTarget->GetActorLocation() + DirToSelf * 80,
			UKismetMathLibrary::MakeRotFromX(FVector(DirToTarget.X, DirToTarget.Y, 0)));
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("111"));

	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("333333333333333333333333"));
	}
}

void ACSpiderManPlayer::SetMovementMode(EMovementMode movementMode)
{
	GetCharacterMovement()->SetMovementMode(movementMode);
}


//Timeline

void ACSpiderManPlayer::WRTUpdate(float Alpha)
{

	SetActorLocationAndRotation(FMath::Lerp(TransitionStartLoc, TransitionEndLoc, Alpha), FMath::Lerp(TransitionStartRot, TransitionEndRot, Alpha));
	WallRunConstantVelocityDirection = GetActorForwardVector();


}

void ACSpiderManPlayer::WRTFinished()
{
	GetCharacterMovement()->MaxAcceleration = 2048;
	isRotationLocked = false;
	isWallRunning = true;
	SpiderState = ESpiderState::WallRunning;
	OpenGate3();
	OpenGate2();

}

void ACSpiderManPlayer::RotToWallUpUpdate(float Alpha) //움직임 없는 중 WallRun 끝낼 때 현재 벽의 위쪽으로 향하는 벡터 그니까 roll이 0이 되도록
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("RotToWallUpdate"));

	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + WallUpRotation.Vector() * 100, FColor::Black, false, 3);

	SetActorRotation(UKismetMathLibrary::RLerp(WallJumpStartRotation, WallUpRotation, Alpha, true));
		
}

void ACSpiderManPlayer::RotToWallUpFinished()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("RotToWallFinished"));

	LaunchCharacter(WallNormal * 500 + FVector(0, 0, 1000), false, false);
	RotBackTimeline.SetPlayRate(1);
	AnimInsRef->isFreezeFallSpeed = true;
	WallRotStart = GetActorRotation();

	RotBackTimeline.PlayFromStart();
}

void ACSpiderManPlayer::RotBackUpdate(float Alpha)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("RotBackUpdate"));

	FRotator WallRotTarget;
	if (AnimInsRef->isFreezeFallSpeed)
	{
		WallRotTarget = UKismetMathLibrary::MakeRotFromX(FVector(WallNormal.X, WallNormal.Y, 0) * -1);
	}
	else
	{
		WallRotTarget = UKismetMathLibrary::MakeRotFromX(FVector(Camera->GetForwardVector().X, Camera->GetForwardVector().Y, 0));

	}
	SetActorRotation(UKismetMathLibrary::RLerp(WallRotStart, WallRotTarget, Alpha, true));
}

void ACSpiderManPlayer::RotBackFinished()
{
	AnimInsRef->isWallJump = false;
	FTimerHandle WaitHandle;
	float WaitTime = 0.4f; //시간을 설정하고
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			isRotationLocked = false;
			SpiderState = ESpiderState::IDLE;

		}), WaitTime, false); 

}

void ACSpiderManPlayer::WebSwingUpdate(float Alpha)
{

	if (!isWebSwinging && !isMovementLocked && GetCharacterMovement()->IsFalling() && ZVelocity < 0 && isAllowNewSwing)
	{
		if (ForLoopForSwingPoints(VisualSwingPoint))
		{
			isWebSwinging = true;
			SpiderState = ESpiderState::Swinging;

			SwingPoint = VisualSwingPoint;
			SetSwingType();
			StartShootWebs();
			SwingForceTimeline.Play();

		}
	}
}

void ACSpiderManPlayer::WebSwingFinished()
{

}

void ACSpiderManPlayer::SwingForceUpdate(float Alpha)
{

	GetCharacterMovement()->AddForce(FindSwingForce()); 

	float ReturnValueRoll, ReturnValuePitch;
	CalculateSwingSideAngle(ReturnValueRoll, ReturnValuePitch);
	FRotator Temp = UKismetMathLibrary::MakeRotator(ReturnValueRoll, ReturnValuePitch, UKismetMathLibrary::MakeRotFromX(GetVelocity()).Yaw);
	FRotator Temp1 = UKismetMathLibrary::RInterpTo(GetActorRotation(), Temp, GetWorld()->DeltaTimeSeconds, 20);
	SetActorRotation(Temp1);
	SwingAngle = CalculateSwingAngle();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("SwingAngle: %f"), SwingAngle));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Current Pitch: %f"), GetActorRotation().Pitch));



}

void ACSpiderManPlayer::SwingForceFinished()
{

}

void ACSpiderManPlayer::WebSourceUpdate(float Alpha)
{
	if (WebToSwing2)
	{
		WebToSwing2->GetParticleSystemComponent()->SetBeamSourcePoint(0, GetMesh()->GetSocketLocation(SwingLocationSocketName), 0);

	}
}

void ACSpiderManPlayer::WebSourceFinished()
{
}

void ACSpiderManPlayer::RotationToZipUpdate(float Alpha)
{
	FRotator Temp = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), BestZipPoint);
	FRotator Temp1 = FMath::Lerp(FRotator(0, ZipBeginRotation.Yaw, 0), FRotator(0, Temp.Yaw, 0), Alpha);
	SetActorRotation(FRotator(ZipBeginRotation.Pitch, Temp1.Yaw, ZipBeginRotation.Roll));

	FRotator Temp2 = UKismetMathLibrary::NormalizedDeltaRotator(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), BestZipPoint), GetActorRotation());
	AnimInsRef->ZipPointAO = Temp2;
}

void ACSpiderManPlayer::RotationToZipFinished()
{
}

void ACSpiderManPlayer::ZipLaunchUpdate()
{
	ZipLaunchUpdateMulti(
		ZipLaunchSpeedCurveFloat->GetFloatValue(ZipLaunchTimeline->GetPlaybackPosition()),
		ZipLaunchUpVectorCurveFloat->GetFloatValue(ZipLaunchTimeline->GetPlaybackPosition())
	);
}

void ACSpiderManPlayer::ZipLaunchFinished()
{
	DestroyWebs();
	isMovementLocked = false;
	isRotationLocked = false;
	AnimInsRef->ZipToPointAnim = EZipToPointState::IDLE;
	

}

void ACSpiderManPlayer::ZipLaunchUpdateMulti(float Value1, float Value2) //1개가 먼저 끝나면 나머지 한개는 마지막수치가 계속 출력됨
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, FString::Printf(TEXT("%f"), Value1));
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("%f"), Value2));

	FVector TempB = AdjustedZipPoint + FVector(0, 0, 100 * Value2);
	SetActorLocation(FMath::Lerp(ZipStartLocation, TempB, Value1));

}

void ACSpiderManPlayer::FreezeUpdate()
{
	SetActorLocation(ZipFreezeVector);
}

void ACSpiderManPlayer::FreezeFinished()
{
}

void ACSpiderManPlayer::DodgeUpdate(float Alpha)
{
	Dodge_SetVelocity(Alpha);
}

void ACSpiderManPlayer::DodgeFinished()
{
	//SpiderState = ESpiderState::IDLE;
	SetBlockPawn();
}

void ACSpiderManPlayer::OnFootAttackHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("HitBoss"));
}

void ACSpiderManPlayer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Enemy") || OtherActor->ActorHasTag("Boss"))
	{
		//class UCDamageType_FlyingPunch* temp = CreateDefaultSubobject<UCDamageType_FlyingPunch>(TEXT("temp"));

		//TSubclassOf<UCDamageType_FlyingPunch> temp2;
		//OtherActor->ReceiveAnyDamage(100, temp, GetController(), this);
		//->TakeDamage(100, temp, GetController(), this);


		FDamageEvent damageEvent;
		//damageEvent = temp;
		FPointDamageEvent pointDamageEvent;
		FHitResult hitResult;
		hitResult.Location = OverlappedComp->GetComponentLocation();
		pointDamageEvent.HitInfo = hitResult;

		//OtherActor->TakeDamage(100, FDamageEvent(temp2), GetController(), this);
		//UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetController(), this, nullptr);
		OtherActor->TakeDamage(100, pointDamageEvent, GetController(), this);
		StopWhenAttack(0.05);

		PlaySoundByName(SoundName::Punch0);
	}

}

void ACSpiderManPlayer::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("HitSomething"));

}

void ACSpiderManPlayer::CustomDelay(float delayTime)
{
	GetWorld()->GetTimerManager().SetTimer(GravityTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			// 코드 구현

			// TimerHandle 초기화
			GetWorld()->GetTimerManager().ClearTimer(GravityTimerHandle);
		}), delayTime, false);
}


