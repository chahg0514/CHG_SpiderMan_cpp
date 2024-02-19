// Fill out your copyright notice in the Description page of Project Settings.


#include "CHealthBar_Enemy.h"
#include "Components/ProgressBar.h"


void UCHealthBar_Enemy::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCHealthBar_Enemy::SetHealth(float health)
{
	HealthBar->SetPercent(health);
}

