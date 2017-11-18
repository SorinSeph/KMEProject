// Fill out your copyright notice in the Description page of Project Settings.

#include "KMEProjectPlayerController.h"
#include "KMEProjectAbilityUpgradeMenu.h"
#include "Engine.h"

AKMEProjectPlayerController::AKMEProjectPlayerController()
{

	/*if (WUpgradeMenu)
	{
		UpgradeMenuRef = CreateWidget<UKMEProjectAbilityUpgradeMenu>(this, WUpgradeMenu);

		UpgradeMenuRef->AddToViewport();
	}*/
}

void AKMEProjectPlayerController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	if (WUpgradeMenu)
	{
		UpgradeMenuRef = CreateWidget<UKMEProjectAbilityUpgradeMenu>(this, WUpgradeMenu);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Possessed called."));

}

void AKMEProjectPlayerController::ToggleUpgradeMenu()
{
	UpgradeMenuRef->AddToViewport();
	UpgradeMenuRef->SetKeyboardFocus();
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}

void AKMEProjectPlayerController::UntoggleUpgradeMenu()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Untoggled menu."));
	UpgradeMenuRef->RemoveFromViewport();
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AKMEProjectPlayerController::SetupInputComponent()

{
	Super::SetupInputComponent();

	InputComponent->BindAction("ExitMenu", IE_Pressed, this, &AKMEProjectPlayerController::UntoggleUpgradeMenu);
}
