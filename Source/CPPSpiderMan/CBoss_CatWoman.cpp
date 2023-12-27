// Fill out your copyright notice in the Description page of Project Settings.


#include "CBoss_CatWoman.h"
#include "CBoss_Parent.h"
#include "CAnimInstance_CatWoman.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CAIController_CatWoman.h"
#include "Engine/EngineTypes.h"
#include "Engine/DamageEvents.h"
#include "CSpiderManPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"
#include "MotionWarpingComponent.h"
//#include "CDamageType_FlyingPunch.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"

//#include "KismetAnimationLibrary.h"


ACBoss_CatWoman::ACBoss_CatWoman()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> HitMtg(TEXT("/Script/Engine.AnimMontage'/Game/catwoman__1_/Animation/HitReact_Left_Montage.HitReact_Left_Montage'"));
	if (HitMtg.Succeeded())
	{
		HitMontage = HitMtg.Object;

	}
	static ConstructorHelpers::FObjectFinder<UAnimationAsset> AnimationAsset(TEXT("/Script/Engine.AnimSequence'/Game/catwoman__1_/Animation/Final/CatDeathBack_Anim.CatDeathBack_Anim'"));
	if (AnimationAsset.Succeeded())
	{
		DeathAnim0 = AnimationAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/catwoman__1_/Catwoman.Catwoman'"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Fired"));
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/catwoman__1_/ABP_CatWoman.ABP_CatWoman_C'"));
	if (AnimAsset.Succeeded())
	{

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("GetAnim"));

		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DataAsset(TEXT("/Script/Engine.DataTable'/Game/catwoman__1_/Data/DT_BossMontage.DT_BossMontage'"));
	if (DataAsset.Succeeded())
	{
		BossMontageDT = DataAsset.Object;
		MontageRowHandle.DataTable = DataAsset.Object;
		MontageRowHandle.RowName = BossMontageName::hitLeft;
	}

	swordComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SwordMeshComp");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SwordMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_HeroSword22/SK_Blade_HeroSword22.SK_Blade_HeroSword22'"));
	if (SwordMeshAsset.Succeeded())
	{
		swordComponent->SetSkeletalMesh(SwordMeshAsset.Object);
	}
	swordComponent->SetupAttachment(GetMesh(), "hand_Sword");
	swordComponent->SetWorldScale3D(FVector(2, 2, 2));


	OnTakeAnyDamage.AddDynamic(this, &ACBoss_CatWoman::TakeAnyDamage);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -95));
	GetMesh()->SetRelativeScale3D(FVector(0.4, 0.4, 0.4));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetGenerateOverlapEvents(true);


	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetCapsuleRadius(28);
	GetCapsuleComponent()->SetCapsuleHalfHeight(96);
	GetCharacterMovement()->MaxWalkSpeed = OriginSpeed;

	Tags.Add("Boss");

	AIControllerClass = ACAIController_CatWoman::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	MotionWarpingComp = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComp_Boss"));
	FMotionWarpingTarget target = {};
	target.Name = FName("BasicAttack");
	MotionWarpingComp->AddOrUpdateWarpTarget(target);
	
}

void ACBoss_CatWoman::BeginPlay()
{
	Super::BeginPlay();
	AnimInsRef = Cast<UCAnimInstance_CatWoman>(GetMesh()->GetAnimInstance());
	TargetSpider = Cast<ACSpiderManPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ACBoss_CatWoman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (AttackAmount > 0)
	{
		IsCanAttack = false;
		AttackAmount = UKismetMathLibrary::Clamp(AttackAmount - DeltaTime, 0, 1000);
	}
	else
	{
		IsCanAttack = true;
	}
}

void ACBoss_CatWoman::SetMontageEnded(FString string)
{

}

void ACBoss_CatWoman::OnWarpMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("OnWarpMontageEnded"));
	MotionWarpingComp->RemoveWarpTarget(FName(*CurrentMontageName));
	BossState = EBossState::Patrol;
}

void ACBoss_CatWoman::HitMontageByDir(float dir)
{
	if (UKismetMathLibrary::InRange_FloatFloat(dir, -45, 45))
	{
		PlayMontageByName(BossMontageName::hitFront);
	}
	else if (UKismetMathLibrary::InRange_FloatFloat(dir, 45, 135))
	{
		PlayMontageByName(BossMontageName::hitRight);
	}
	else if (UKismetMathLibrary::InRange_FloatFloat(dir, -135, -45))
	{
		PlayMontageByName(BossMontageName::hitLeft);
	}
	else
	{
		PlayMontageByName(BossMontageName::hitBack);
	}
}

void ACBoss_CatWoman::PlayMontageByName(FName name)
{
	MontageRowHandle.RowName = name;
	FBossMontage temp = *BossMontageDT->FindRow<FBossMontage>(MontageRowHandle.RowName, TEXT(""));

	if (&temp != nullptr)
	{
		PlayAnimMontage(temp.Montage);
	}

}

void ACBoss_CatWoman::PlayDeathMontage(FName name)
{
	if (BossMontageDT)
	{
		UAnimMontage* montage = BossMontageDT->FindRow<FBossMontage>(name, TEXT(""))->Montage;
		if (montage)
		{
			float temp = PlayAnimMontage(montage);

			FTimerHandle myTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(myTimerHandle, FTimerDelegate::CreateLambda([&]()
				{
					// 내가 원하는 코드 구현
					GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
					GetMesh()->SetSimulatePhysics(true);

					// 타이머 초기화
					GetWorld()->GetTimerManager().ClearTimer(myTimerHandle);
				}), 1.2, false);

		}
	}
}

void ACBoss_CatWoman::SetWarpTarget(FName name, FVector vector)
{
	MotionWarpingComp->AddOrUpdateWarpTargetFromLocation(name, vector);
}

float ACBoss_CatWoman::PlayWarpMontage(FName name)
{
	if (BossMontageDT)
	{
		UAnimMontage* montage = BossMontageDT->FindRow<FBossMontage>(name, TEXT(""))->Montage;
		if (montage)
		{
			CurrentMontageName = name.ToString();
			float temp = PlayAnimMontage(montage);

			FOnMontageEnded endDelegate;
			endDelegate.BindUObject(this, &ACBoss_CatWoman::OnWarpMontageEnded);
			AnimInsRef->Montage_SetEndDelegate(endDelegate, montage);

			return temp;
		}
	}
	return 0;
}

void ACBoss_CatWoman::EndAllState()
{
	
	StopAnimMontage();
	BossState = EBossState::Patrol; //이때 너무 먼 거리에 있으면 점프해서 플레이어쪽으로 날아오는거임
}



void ACBoss_CatWoman::BasicAttack()
{

}



void ACBoss_CatWoman::SetDisBeforePatrol()
{
	if (GetDisBetweenPlayer() > 2000) //수치 조정 필요
	{

	}
}

void ACBoss_CatWoman::SetWalkSpeed(float value)
{
	GetCharacterMovement()->MaxWalkSpeed = value;
}



float ACBoss_CatWoman::GetDisBetweenPlayer()
{
	if (TargetSpider)
	{
		return UKismetMathLibrary::Vector_Distance(GetActorLocation(), TargetSpider->GetActorLocation());
	}
	return 0.0f;
}





bool ACBoss_CatWoman::MoveToPlayerByDistance() //Distance로 캐릭터에게 다가가고, 거리 내라면 true 반환
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("MoveToPlayer"));
	if (GetDisBetweenPlayer() <= AttackDistance)
	{
		GetCharacterMovement()->StopMovementImmediately();
		return true;
	}
	else
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), TargetSpider->GetActorLocation());
		return false;
	}
}

void ACBoss_CatWoman::SetCirclePatrolTargetVector(FVector& target)
{

	if (isSetPatrolTarget)
	{

		return;
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("SetMoveVector"));
		if (UKismetMathLibrary::RandomIntegerInRange(0, 1) == 0)
		{
			//왼쪽
			target = GetActorLocation() + GetActorForwardVector() * 400 + GetActorRightVector() * -10;
			PatrolTargetVector = target;
			//속도 느리게?
			isSetPatrolTarget = true;
			return;
		}
		else
		{
			//오른쪽
			target = GetActorLocation() + GetActorForwardVector() * 400 + GetActorRightVector() * 10;
			PatrolTargetVector = target;
			//속도 느리게?
			isSetPatrolTarget = true;
			return;
		}
	}
}

bool ACBoss_CatWoman::MoveToPatrolVector()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("MoveToPatrolVector"));
	if (isSetPatrolTarget && BossState == EBossState::Patrol)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), FVector(PatrolTargetVector.X, PatrolTargetVector.Y, GetActorLocation().Z));
		if (UKismetMathLibrary::Vector_Distance(GetActorLocation(), PatrolTargetVector) <= 45)
		{
			isSetPatrolTarget = false;
			//속도 원래대로?
			return true;
		}
		return false;
	}
	return false;
}

void ACBoss_CatWoman::SetNextAttackType() //거리가 가까우면 바로 할 수 있는것과 달려가서 시작해야하는 스킬 나누기
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("SetAttackType"));

	if (GetDisBetweenPlayer() < 400)
	{
		int type = UKismetMathLibrary::RandomIntegerInRange(0, 3);
		switch (type)
		{
		case 0:
			BossState = EBossState::BasicAttack;
			AttackDistance = 150;
			GetCharacterMovement()->MaxWalkSpeed = 350;
			isSetAttackType = true;
			break;
		case 1:
			BossState = EBossState::FireShot;
			AttackDistance = 150;
			GetCharacterMovement()->MaxWalkSpeed = 350;
			isSetAttackType = true;
			break;
		case 2:
			BossState = EBossState::Dash;
			AttackDistance = 150;
			GetCharacterMovement()->MaxWalkSpeed = 350;
			isSetAttackType = true;
			break;
		case 3:
			BossState = EBossState::BasicAttack;
			AttackDistance = 150;
			GetCharacterMovement()->MaxWalkSpeed = 350;
			isSetAttackType = true;
			break;
		}
	}
	
	
	

}

void ACBoss_CatWoman::StartAttack()
{
	switch (BossState)
	{
	case EBossState::BasicAttack:
		PlayMontageByName(BossMontageName::basicAttack);
		break;
	case EBossState::Patrol:
		break;
	case EBossState::FireShot:
		break;
	case EBossState::Dash:
		break;
	case EBossState::Stunned:
		break;
	default:
		break;
	}
}

void ACBoss_CatWoman::ApplyDamage()
{
	FVector Start = GetActorLocation();
	FVector End = GetActorLocation() + GetActorForwardVector() * 150;
	TArray<AActor*> Ignore;
	Ignore.Add(this);
	TArray<FHitResult> OutHits;

	FHitResult hitResult;
	if (UKismetSystemLibrary::CapsuleTraceMulti(GetWorld(), Start, End, 40, 100, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), true, Ignore,
		EDrawDebugTrace::None, OutHits, true, FLinearColor::Yellow))
	{

		for (auto i : OutHits)
		{

			ACSpiderManPlayer* target = Cast<ACSpiderManPlayer>(i.GetActor());
			if (target)
			{
				FPointDamageEvent pointDamageEvent;
				FHitResult pointHitResult;
				hitResult.Location = i.Location;
				pointDamageEvent.HitInfo = pointHitResult;
				//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Result"));
				target->TakeDamage(50, pointDamageEvent, GetController(), this);

			}
		}

	}
}

void ACBoss_CatWoman::WhenEndStateCompletely()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("EndState"));
	switch (BossState)
	{
	case EBossState::BasicAttack:
		isSetPatrolTarget = false;
		isSetAttackType = false;
		BossState = EBossState::Patrol;
		GetCharacterMovement()->MaxWalkSpeed = OriginSpeed;
		break;
	case EBossState::Patrol:
		GetCharacterMovement()->StopMovementImmediately();
		//GetCharacterMovement()->MaxWalkSpeed = OriginSpeed;
		SetNextAttackType();
		isSetPatrolTarget = false;
		break;
	case EBossState::FireShot:
		break;
	case EBossState::Dash:
		break;
	case EBossState::Stunned:
		BossState = EBossState::Patrol;
		break;
	default:
		break;
	}
}

void ACBoss_CatWoman::StartLeap()
{
	GetCharacterMovement()->StopMovementImmediately();
}

bool ACBoss_CatWoman::IsCloseToPlayer()
{
	if (GetDisBetweenPlayer() < LeapDistance)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Close"));
		return true;
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Fall"));
	return false;
}

void ACBoss_CatWoman::LeapToLocation(FVector loc)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), loc);
	if (UKismetMathLibrary::Vector_Distance(GetActorLocation(), loc) <= 45)
	{
		BossState = EBossState::Patrol;
		IsLeaping = false;
	}

}

void ACBoss_CatWoman::SetMotionWarpTarget(FVector vector)
{

}

void ACBoss_CatWoman::HitFlyingPunch()
{
	StopAnimMontage();
	BossState = EBossState::Stunned;
}

float ACBoss_CatWoman::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//데미지 들어오면 Patrol끝내고 EndPatrol로 바꾸고, tree에서 set attack type 할 수 있도록
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (currentHP == 0)
	{
		//CatDeathMontage();
	}

	/*if (DamageEvent.ClassID == UCDamageType_FlyingPunch::StaticClass())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("DamageTypeFlyingPunch"));
	}*/

	if (DamageEvent.IsOfType(FDamageEvent::ClassID))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("Damage"));
		//이거랑 포인트 데미지랑 같이 실행됨

	}
	//DamageEvent.DamageTypeClass
	//PointDamage 받기
	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		if (BossState == EBossState::Patrol)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("TakeDamage"));

			BossState = EBossState::Stunned;
			GetCharacterMovement()->StopMovementImmediately();
			//WhenEndStateCompletely();
			FHitResult hitResult;
			FVector temp;
			DamageEvent.GetBestHitInfo(nullptr, nullptr, hitResult, temp);

			FVector start, target;

			start = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
			target = FVector(hitResult.Location.X, hitResult.Location.Y, 0);

			//여기서 SpawnActor 해봐서 위치 테스트해봄

			FVector velocity = UKismetMathLibrary::FindLookAtRotation(start, target).Vector();



			float dir = UKismetAnimationLibrary::CalculateDirection(velocity, GetActorRotation());
			HitMontageByDir(dir);
		}

	}


	return Damage;
}

void ACBoss_CatWoman::TakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Black, TEXT("TakeAnyDamage"));
}

void ACBoss_CatWoman::OnMotionWarpMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
}

void ACBoss_CatWoman::CatDeathMontage(float DotResult)
{
	PlayMontageByName(BossMontageName::deathBack);
	//GetMesh()->PlayAnimation(DeathAnim0, false);
	StopAnimMontage();
	GetCharacterMovement()->StopMovementImmediately();
	BossState = EBossState::Stunned;
	FTimerHandle myTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(myTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			// 내가 원하는 코드 구현
			GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
			GetMesh()->SetSimulatePhysics(true);

			// 타이머 초기화
			GetWorld()->GetTimerManager().ClearTimer(myTimerHandle);
		}), 2, false);
	/*if (DotResult > 0)
	{
		PlayDeathMontage(BossMontageName::deathBack);
	}
	else
	{
		PlayDeathMontage(BossMontageName::deathFront);

	}*/
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Black, TEXT("CatDeath"));
}
