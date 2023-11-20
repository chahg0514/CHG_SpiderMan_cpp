// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Particles/Emitter.h"
#include "CWebToSwing.generated.h"

/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API ACWebToSwing : public AEmitter
{
	GENERATED_BODY()
public:
	ACWebToSwing();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	class UParticleSystem* Web_Swing;

public:
	//, OverrideNativeName = "kkkkkkk"
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WebToSwing", meta = (ExposeOnSpawn = "true"))
		FVector Target = FVector(0, 0, 200);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WebToSwing", meta = (ExposeOnSpawn = "true"))
		FVector Source = FVector(0, 0, 0);
	
};
