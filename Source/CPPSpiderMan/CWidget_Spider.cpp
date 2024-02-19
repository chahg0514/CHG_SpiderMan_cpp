// Fill out your copyright notice in the Description page of Project Settings.


#include "CWidget_Spider.h"
#include "Components/ProgressBar.h"

void UCWidget_Spider::SetHealth(float health)
{
	HealthBar->SetPercent(health);
}
