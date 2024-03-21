// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CBoss_Parent.generated.h"

UCLASS()
class CPPSPIDERMAN_API ACBoss_Parent : public ACharacter
{
	GENERATED_BODY()



public:
	// Sets default values for this character's properties
	ACBoss_Parent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//MSB3073, uproperty 다 빼버림
protected:
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = true))
		TSubclassOf<class UUserWidget> HealthBarClass;


	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
		float damage = 10.f;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
		float currentHP = 10000.f;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
		float maxHP = 10000.f;

protected:

	class UCHealthBar_Boss* selfHpBar_Boss;


protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void CatDeathMontage(float DotResult);
};
