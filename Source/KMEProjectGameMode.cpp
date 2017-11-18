// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "KMEProjectGameMode.h"
#include "KMEProjectHUD.h"
#include "KMEProjectCharacter.h"
#include "KMEProjectPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AKMEProjectGameMode::AKMEProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AKMEProjectHUD::StaticClass();

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/BP_PlayerController"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;
}
