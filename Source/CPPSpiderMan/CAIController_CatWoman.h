// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Perception/AIPerceptionTypes.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController_CatWoman.generated.h"

/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API ACAIController_CatWoman : public AAIController
{
	GENERATED_BODY()
public:
	ACAIController_CatWoman();

protected:
	virtual void OnPossess(APawn* InPawn) override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception", meta = (AllowPrivateAccess = true))
		class UAISenseConfig_Sight* SightConfig;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception", meta = (AllowPrivateAccess = true))
		class UBehaviorTree* BTree;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception", meta = (AllowPrivateAccess = true))
		class UBlackboardComponent* BBComp;
private:
	UFUNCTION(BlueprintCallable, Category = "Perception")
		void OnTargetDetected(AActor* InActor, FAIStimulus Stimulus);

	class ACSpiderManPlayer* Target;

};
