// Copyright Epic Games, Inc. All Rights Reserved.


#include "CPPSpiderManGameModeBase.h"

#include "CSpiderManPlayer.h"
#include "CSpiderManController.h"

ACPPSpiderManGameModeBase::ACPPSpiderManGameModeBase()
{
	DefaultPawnClass = ACSpiderManPlayer::StaticClass();
	PlayerControllerClass = ACSpiderManController::StaticClass();

}

void ACPPSpiderManGameModeBase::BeginPlay()
{
}

