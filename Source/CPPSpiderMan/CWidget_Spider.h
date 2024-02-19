// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_Spider.generated.h"

/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API UCWidget_Spider : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		class UProgressBar* HealthBar;

public:
	void SetHealth(float health);
	
};
