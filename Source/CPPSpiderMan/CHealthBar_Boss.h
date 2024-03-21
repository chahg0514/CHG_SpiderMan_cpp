// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHealthBar_Boss.generated.h"

/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API UCHealthBar_Boss : public UUserWidget
{
	GENERATED_BODY()
protected:

	virtual void NativeConstruct() override;
	//MSB3073
private:
	//UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		class UProgressBar* HealthBar;

public:
	void SetHealth(float health);
	
	
};
