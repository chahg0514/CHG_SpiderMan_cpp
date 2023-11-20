// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy_Parent.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "CSpiderManPlayer.h"
#include "CHealthBar_Enemy.h"


// Sets default values
ACEnemy_Parent::ACEnemy_Parent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> HealthWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BPHealthBar_Enemy.BPHealthBar_Enemy_C'"));
	if (HealthWidgetClass.Succeeded())
	{
		HealthBarClass = HealthWidgetClass.Class;
	}
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidgetComponent"));
	WidgetComp->SetupAttachment(GetCapsuleComponent());
	WidgetComp->SetWidgetClass(HealthBarClass);
	WidgetComp->SetWorldScale3D(FVector(0.5, 0.35, 0.25));
	WidgetComp->SetRelativeLocation(FVector(0, 0, 110));
	GetCapsuleComponent()->SetCapsuleRadius(28);
}

// Called when the game starts or when spawned
void ACEnemy_Parent::BeginPlay()
{
	Super::BeginPlay();
	selfHpBar_Enemy = Cast<UCHealthBar_Enemy>(WidgetComp->GetWidget());
	Player = Cast<ACSpiderManPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ACEnemy_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Player)
	{
		WidgetComp->SetWorldRotation(Player->ReturnCameraRotation());
	}
}

// Called to bind functionality to input
void ACEnemy_Parent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACEnemy_Parent::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* Causer)
{
	if (selfHpBar_Enemy)
	{
		currentHP -= Damage;
		if (currentHP <= 0)
		{
			Destroy();
			return Damage;
		} 
		selfHpBar_Enemy->SetHealth(FMath::Clamp((currentHP), 0, maxHP) / maxHP);
	}
	return Damage;
}

