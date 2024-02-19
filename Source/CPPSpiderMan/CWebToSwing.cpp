// Fill out your copyright notice in the Description page of Project Settings.


#include "CWebToSwing.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

ACWebToSwing::ACWebToSwing()
{
	Web_Swing = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, TEXT("/Script/Engine.ParticleSystem'/Game/FX/Webs/Web_Swing.Web_Swing'")));
	if (Web_Swing)
	{
		SetTemplate(Web_Swing);
		
	}

}

void ACWebToSwing::BeginPlay()
{
	//GetParticleSystemComponent()->SetBeamTargetPoint(0, Target, 0);
	//GetParticleSystemComponent()->SetBeamSourcePoint(0, Source, 0);

}
