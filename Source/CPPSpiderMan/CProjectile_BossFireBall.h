// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CProjectile_BossFireBall.generated.h"

UCLASS()
class CPPSPIDERMAN_API ACProjectile_BossFireBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACProjectile_BossFireBall();

private:
	FVector TargetLocation;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	


	void LaunchProjectile(FVector EndPos);


	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* Particle;
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacking Collusion")
	class USphereComponent* AttackCollision;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



};
