// Fill out your copyright notice in the Description page of Project Settings.


#include "CProjectile_BossFireBall.h"

#include "CBoss_CatWoman.h"
#include "Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CDamageType_CatStunAttack.h"

// Sets default values
ACProjectile_BossFireBall::ACProjectile_BossFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Attacking Collision"));
	AttackCollision->InitSphereRadius(50.f);
	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ACProjectile_BossFireBall::OnOverlapBegin);
	AttackCollision->SetCollisionProfileName(TEXT("EnemyAttack"));
	RootComponent = AttackCollision;
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	Particle->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> particle(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonTwinblast/FX/Particles/Abilities/Ultimate/FX/P_TwinBlast_Ult2_MuzzleFlash.P_TwinBlast_Ult2_MuzzleFlash'"));
	if (particle.Succeeded())
	{
		Particle->SetTemplate(particle.Object);
	}
	//Particle->SetWorldRotation(FRotator(0, 180, 0));
	Particle->SetRelativeScale3D(FVector(0.5, 3, 3));
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileComponent->bRotationFollowsVelocity = true;
	
	//AttackCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//AttackCollision->SetupAttachment(RootComponent);
	

}



// Called when the game starts or when spawned
void ACProjectile_BossFireBall::BeginPlay()
{
	Super::BeginPlay();
	//UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVel, )
	//ProjectileComponent->AddImp
	
}

// Called every frame
void ACProjectile_BossFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Particle->SetRelativeRotation(UKismetMathLibrary::MakeRotFromX(TargetLocation - GetActorLocation()));

}

void ACProjectile_BossFireBall::LaunchProjectile(FVector EndPos)
{
	TargetLocation = EndPos;
	FVector outVel;
	if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVel, GetActorLocation(), EndPos))
	{
		FPredictProjectilePathParams predictParams(20.0f, GetActorLocation(), outVel, 15.0f);   // 20: tracing 보여질 프로젝타일 크기, 15: 시물레이션되는 Max 시간(초)
		predictParams.DrawDebugTime = 15.0f;     //디버그 라인 보여지는 시간 (초)
		predictParams.DrawDebugType = EDrawDebugTrace::Type::ForDuration;  // DrawDebugTime 을 지정하면 EDrawDebugTrace::Type::ForDuration 필요.
		predictParams.OverrideGravityZ = GetWorld()->GetGravityZ();
		FPredictProjectilePathResult result;
		//UGameplayStatics::PredictProjectilePath(this, predictParams, result);
		ProjectileComponent->Velocity = outVel;
	}
	
}

void ACProjectile_BossFireBall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Enemy"))
	{
		Destroy();
		return;
	}
	if (Cast<APawn>(OtherActor))
	{
		TSubclassOf<UCDamageType_CatStunAttack> temp(UCDamageType_CatStunAttack::StaticClass());

		UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetInstigator()->GetController(), this, temp);
		//GetInstigator()->GetController()->GetCharacter();//GetPawn이랑 똑같은데 컨트롤러의 Pawn이 Character가 아니라면 이 함수는 nullptr
		/*if (Cast<ACBoss_CatWoman>(GetInstigator()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("CatWomanIsInstigator"));

		}*/
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("FireBallOverlap"));
		
	}
	Destroy();
	
}

