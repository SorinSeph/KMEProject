// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KMEProjectInventoryItem.generated.h"

UENUM(BlueprintType)
enum EItemType
{
	HealingPlant,
	HealingMeds,
	Knife,
	Gun,
	Gun2,
	Shotgun,
	Rifle,
	GunAmmo,
	Gun2Ammo,
	ShotgunAmmo,
	RifleAmmo
};


UCLASS()
class KMEPROJECT_API AKMEProjectInventoryItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKMEProjectInventoryItem();

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Attachment)
	FName PrimarySocket;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
