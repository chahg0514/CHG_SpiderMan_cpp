// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TimelineComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLandPredictionCurve.generated.h"

UCLASS()
class CPPSPIDERMAN_API ACLandPredictionCurve : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACLandPredictionCurve();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTimelineComponent* ExampleTimelineComp;

public:

	UPROPERTY(EditAnywhere)
		UCurveFloat* ExampleTimelineCurve;

};
