// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CSpiderManController.generated.h"

/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API ACSpiderManController : public APlayerController
{
	GENERATED_BODY()
public:
	ACSpiderManController();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
private:
	UFUNCTION()
		void MoveForward(float Axis);
	UFUNCTION()
		void MoveRight(float Axis);
	UFUNCTION()
		void Zoom(float Axis);
	UFUNCTION()
		void Turn(float Axis);
	UFUNCTION()
		void LookUp(float Axis);
	UFUNCTION()
		void PlayerJump();
	UFUNCTION()
		void PlayerJumpRelease();
	UFUNCTION()
		void PlayerAttack();
	UFUNCTION()
		void ShowInventory();
	UFUNCTION()
		void LeftShiftDown();
	UFUNCTION()
		void LeftShiftUp();
	UFUNCTION()
		void ZipToPoint();
	UFUNCTION()
		void BasicAttack();
	UFUNCTION()
		void ObjectAttack();
	UFUNCTION()
		void Dodge();
	UFUNCTION()
		void FlyingPunch();
	UFUNCTION()
		void TestMontage();
	FVector FindForwardSwingForce();
	FVector FindRightSwingForce();

private:
	UPROPERTY(VisibleAnywhere, Category = "Player")
		class ACSpiderManPlayer* MyPlayer;

	
	
};
