


// Fill out your copyright notice in the Description page of Project Settings.


#include "CSpiderManController.h"

#include "CSpiderManPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

ACSpiderManController::ACSpiderManController()
{
	
}

void ACSpiderManController::Tick(float DeltaTime)
{
	
}

void ACSpiderManController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (!IsValid(InPawn)) return;
	MyPlayer = Cast<ACSpiderManPlayer>(InPawn);
}

void ACSpiderManController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis(TEXT("MoveForward"), this, &ACSpiderManController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ACSpiderManController::MoveRight);
	//InputComponent->BindAxis(TEXT("Zoom"), this, &ACSpiderManController::Zoom);
	InputComponent->BindAxis(TEXT("Turn"), this, &ACSpiderManController::Turn);
	InputComponent->BindAxis(TEXT("LookUp"), this, &ACSpiderManController::LookUp);
	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACSpiderManController::PlayerJump);
	InputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACSpiderManController::PlayerJumpRelease);
	InputComponent->BindAction(TEXT("ObjectAttack"), IE_Pressed, this, &ACSpiderManController::ObjectAttack);

	InputComponent->BindAction(TEXT("Swing"), IE_Pressed, this, &ACSpiderManController::LeftShiftDown);
	InputComponent->BindAction(TEXT("Swing"), IE_Released, this, &ACSpiderManController::LeftShiftUp);

	InputComponent->BindAction(TEXT("ZipToPoint"), IE_Pressed, this, &ACSpiderManController::ZipToPoint);
	InputComponent->BindAction(TEXT("BasicAttack"), IE_Pressed, this, &ACSpiderManController::BasicAttack);
	InputComponent->BindAction(TEXT("Dodge"), IE_Pressed, this, &ACSpiderManController::Dodge);
	InputComponent->BindAction(TEXT("FlyingPunch"), IE_Pressed, this, &ACSpiderManController::FlyingPunch);
	InputComponent->BindAction(TEXT("TestMontage"), IE_Pressed, this, &ACSpiderManController::TestMontage);
	//InputComponent->BindAction(TEXT("ObjectAttack"), IE_Pressed, this, &ACSpiderManController::);

	



	//InputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ACSpiderManController::PlayerAttack);
	//InputComponent->BindAction(TEXT("Inventory"), IE_Pressed, this, &ACSpiderManController::ShowInventory);
}

void ACSpiderManController::MoveForward(float Axis)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Axis: %f"), Axis));

	if (MyPlayer->GetIsMovable())
	{
		

	}

	if (Axis != 0.0f && MyPlayer->GetIsMovable())
	{
		
		if (MyPlayer->GetIsWallRunning())
		{
			GetPawn()->AddMovementInput(MyPlayer->FindWallRunForwardVector(), Axis);

			return;
		}
		if (MyPlayer->GetIsWebSwinging())
		{
			MyPlayer->GetCharacterMovement()->AddForce(FindForwardSwingForce());
			return;
		}

		const FRotator Rot = GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		GetPawn()->AddMovementInput(Direction, Axis);
		MyPlayer->StopPerch();
	}
}

void ACSpiderManController::MoveRight(float Axis)
{
	if (Axis != 0.0f && MyPlayer->GetIsMovable())
	{
		if (MyPlayer->GetIsWallRunning())
		{

			GetPawn()->AddMovementInput(MyPlayer->FindWallRunRightVector(), -Axis);


			return;
		}
		if (MyPlayer->GetIsWebSwinging())
		{
			MyPlayer->GetCharacterMovement()->AddForce(FindRightSwingForce());

			return;
		}
		const FRotator Rot = GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
		GetPawn()->AddMovementInput(-Direction, Axis);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("WallRunRight"));
		MyPlayer->StopPerch();
	}
}

void ACSpiderManController::Zoom(float Axis)
{
}

void ACSpiderManController::Turn(float Axis)
{
	AddYawInput(Axis);
}

void ACSpiderManController::LookUp(float Axis)
{
	AddPitchInput(Axis);
}

void ACSpiderManController::PlayerJump()
{
	if (IsValid(MyPlayer))
	{
		MyPlayer->SpiderJumpPress();
	}
}

void ACSpiderManController::PlayerJumpRelease()
{
	if (IsValid(MyPlayer))
	{
		MyPlayer->SpiderJumpRelease();
	}
}

void ACSpiderManController::PlayerAttack()
{
}

void ACSpiderManController::ShowInventory()
{
}

void ACSpiderManController::LeftShiftDown()
{
	MyPlayer->SetIsLeftShift(true);
	MyPlayer->GetCharacterMovement()->MaxWalkSpeed = 1200;
	MyPlayer->GetCharacterMovement()->MaxFlySpeed = 1600;
	MyPlayer->StartTryingToSwing();
}

void ACSpiderManController::LeftShiftUp()
{
	MyPlayer->SetIsLeftShift(false);
	MyPlayer->GetCharacterMovement()->MaxWalkSpeed = 600;
	MyPlayer->GetCharacterMovement()->MaxFlySpeed = 500;
	MyPlayer->StopTryingToSwing();
}

void ACSpiderManController::ZipToPoint()
{
	MyPlayer->ZipToPoint();
}

void ACSpiderManController::BasicAttack()
{
	MyPlayer->BasicAttack();
}

void ACSpiderManController::ObjectAttack()
{
	MyPlayer->ObjectAttack();
}

void ACSpiderManController::Dodge()
{
	MyPlayer->DodgeInput();
}

void ACSpiderManController::FlyingPunch()
{
	MyPlayer->FlyingAttackInput();
}

void ACSpiderManController::TestMontage()
{
	MyPlayer->TestMontageInput();
}

void ACSpiderManController::SetCanZipToPoint()
{
	MyPlayer->SetIsCanZipPointUI();
}

FVector ACSpiderManController::FindForwardSwingForce()
{
	FVector Temp = FVector(GetControlRotation().Vector().X, GetControlRotation().Vector().Y, 0).GetSafeNormal();
	float TempFloat = UKismetMathLibrary::Clamp(MyPlayer->GetVelocity().Size(), 0, 1000);

	return Temp * TempFloat * 10;
}

FVector ACSpiderManController::FindRightSwingForce()
{
	FVector Temp = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y);
	FVector Temp1 = FVector(Temp.X, Temp.Y, 0).GetSafeNormal();
	float TempFloat = UKismetMathLibrary::Clamp(MyPlayer->GetVelocity().Size(), 0, 1000);

	return Temp * TempFloat * 100;
}
