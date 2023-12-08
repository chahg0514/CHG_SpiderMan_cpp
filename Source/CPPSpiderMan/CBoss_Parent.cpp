// Fill out your copyright notice in the Description page of Project Settings.


#include "CBoss_Parent.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


#include "CHealthBar_Boss.h"


// Sets default values
ACBoss_Parent::ACBoss_Parent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> HealthWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BPHealthBar_Boss.BPHealthBar_Boss_C'"));
	if (HealthWidgetClass.Succeeded())
	{
		HealthBarClass = HealthWidgetClass.Class;
	}
}

// Called when the game starts or when spawned
void ACBoss_Parent::BeginPlay()
{
	Super::BeginPlay();
	selfHpBar_Boss = Cast<UCHealthBar_Boss>(CreateWidget<UUserWidget>(GetWorld(), HealthBarClass));
	if (selfHpBar_Boss)
	{
		selfHpBar_Boss->AddToViewport();
	}
}

// Called every frame
void ACBoss_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACBoss_Parent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACBoss_Parent::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float DotResult = DamageCauser->GetActorForwardVector().Dot(GetActorForwardVector());

	FMath::Clamp(currentHP -= Damage, 0, maxHP);
	selfHpBar_Boss->SetHealth(currentHP / maxHP);
	if (currentHP == 0)
	{
		//When Boss Die
		CatDeathMontage(DotResult);
		return DamageAmount; //일단 return을 뭐라도 해줘야하니깐
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("acceptDamageInBossParent"));
	return DamageAmount;
}

void ACBoss_Parent::CatDeathMontage(float DotResult)
{
}


