// Fill out your copyright notice in the Description page of Project Settings.


#include "CHealthBar_Boss.h"
#include "Components/ProgressBar.h"

void UCHealthBar_Boss::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCHealthBar_Boss::SetHealth(float health)
{
	HealthBar->SetPercent(health);
}
