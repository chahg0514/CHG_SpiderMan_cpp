// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPPSpiderManGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CPPSPIDERMAN_API ACPPSpiderManGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	ACPPSpiderManGameModeBase();

protected:
	virtual void BeginPlay() override;
	
};
