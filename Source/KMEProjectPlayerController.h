// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KMEProjectPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KMEPROJECT_API AKMEProjectPlayerController : public APlayerController
{
	GENERATED_BODY()
		
public:
	
	AKMEProjectPlayerController();
	
	virtual void Possess(APawn* InPawn) override;

	void ToggleUpgradeMenu();

	void UntoggleUpgradeMenu();

protected:

	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, Category = Menu)
	TSubclassOf <class UKMEProjectMainMenuUI > WMainMenu;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TSubclassOf <class UKMEProjectAbilityUpgradeMenu > WUpgradeMenu;

	class UKMEProjectAbilityUpgradeMenu* UpgradeMenuRef;
	
	
};
