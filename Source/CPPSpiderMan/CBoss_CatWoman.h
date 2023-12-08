// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "CBoss_Parent.h"
#include "CBoss_CatWoman.generated.h"

UENUM(BlueprintType)
enum class EBossState : uint8
{
	BasicAttack UMETA(DisplayName = "basicAttack"), //캐릭터에게 뛰어온 후 일정 거리가 되면 빠른 기본공격
	Leap UMETA(DisplayName = "leap"), //Patrol중 IsCloseToLeap이 true면 eqs실행 후 Leap으로 진입, Leap이면 
	Patrol UMETA(DisplayName = "patrol"), //플레이어와 거리가 멀면 다가옴, 가까우면 플레이어 주위를 원형으로 걸어다님. 기본 상태
	EndPatrol UMETA(DisplayName = "endPatrol"), 
	SetNextAttack UMETA(DisplayName = "setNextAttack"), //다음 공격 지정하는 상태
	Skill1 UMETA(DisplayName = "skill1"), //플레이어 위치로 돌진공격 1회, 제자리 공격 2회
	Skill2 UMETA(DisplayName = "skill2"),
	Stunned UMETA(DisplayName = "stunned") //기본공격 맞을 때 Patrol 상태라면 스턴, FlyingPunch 공격 들어오면 무조건 스턴
	//스킬 시전 후 재정비하는 애니메이션 구하면 스테이트 추가
};
USTRUCT(Atomic, BlueprintType)
struct FBossMontage : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemData")
		FString Name = FString(TEXT(""));
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemData")
		class UAnimMontage* Montage;

};
namespace BossMontageName
{
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MontageName")
	const FName hitLeft = TEXT("HitLeft");
	const FName hitRight = TEXT("HitRight");
	const FName hitFront = TEXT("HitFront");
	const FName hitBack = TEXT("HitBack");
	const FName basicAttack = TEXT("BasicAttack");
	const FName leap = TEXT("Leap");
	const FName deathFront = TEXT("DeathFront");
	const FName deathBack = TEXT("DeathBack");


}
/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API ACBoss_CatWoman : public ACBoss_Parent
{
	GENERATED_BODY()
public:
	ACBoss_CatWoman();

protected:
	virtual void BeginPlay() override;

	
private:
	UPROPERTY(EditAnywhere, Category = "MontageData")
		class UDataTable* BossMontageDT;
	UPROPERTY(EditAnywhere, Category = "MontageData")
		struct FDataTableRowHandle MontageRowHandle;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
		class UAnimMontage* HitMontage;
	class USkeletalMeshComponent* swordComponent;
	class ACSpiderManPlayer* TargetSpider;
	class UCAnimInstance_CatWoman* AnimInsRef;
private:
	
	//Montage Related Function
	void SetMontageEnded(FString string); //WarpTarget Remove하기 위해 현재 상태에 따라 이름으로 몽타주 끝내기
	UFUNCTION()
		void OnWarpMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	

	void HitMontageByDir(float dir);

	void PlayMontageByName(FName name); //몽타주만 실행\
	//Death
	void PlayDeathMontage(FName name);

public:
	void SetWarpTarget(FName name, FVector vector);
	float PlayWarpMontage(FName name); //몽타주 실행, 끝나면 해당 이름의 워프타겟 삭제
private:
	FString CurrentMontageName;

	void EndAllState(); //현재의 상태를 전부 취소함. 절대적인 우선순위의 스킬을 위해(Flying Punch)

	//Combat
	
	float AttackDistance = 500;
	
	void BasicAttack();

	//Patrol

	//Leap
	float LeapDistance = 200;

	UAnimationAsset* DeathAnim0;
public:

	UPROPERTY(BlueprintReadWrite)
	bool isSetPatrolTarget = false;
private:
	FVector PatrolTargetVector;
	

	void SetDisBeforePatrol();

	

	//MoveTo
	float GetDisBetweenPlayer();
	float OriginSpeed = 150;

	
	


	
public:
	//MotionWarping
	UPROPERTY(BlueprintReadWrite, Category = "MotionWarping")
		TObjectPtr<class UMotionWarpingComponent> MotionWarpingComp;
	void SetMotionWarpTarget(FVector vector);

	
	//Hit
	void HitFlyingPunch();


	//SetWalkSpeed
	void SetWalkSpeed(float value);

	//MoveTo
	bool MoveToPlayerByDistance();

	//Patrol
	void SetCirclePatrolTargetVector(FVector& target);
	bool MoveToPatrolVector();

	//Combat
	void SetNextAttackType();
	void StartAttack();
	void ApplyDamage();
	

	//EndState
	void WhenEndStateCompletely(); //몽타주 끝부분에 실행. 각 상태의 마무리에 해줘야하는 설정 switch로 설정

	//Leap
	void StartLeap();
	bool IsCloseToPlayer(); //If Close enough to play Leap State, return true
	bool IsLeaping = false;
	FVector LeapLocation;
	void LeapToLocation(FVector loc);

	

	


public:
	UPROPERTY(BlueprintReadWrite)
	EBossState BossState = EBossState::Patrol;
	bool isSetAttackType = false;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
private:
	void TakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
		void OnMotionWarpMontageEnded(UAnimMontage* Montage, bool bInterrupted);

protected:
	virtual void CatDeathMontage(float DotResult) override;


};
