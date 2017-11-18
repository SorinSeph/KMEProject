// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KMEProjectLockpickPawn.h"
#include "KMEProjectLockpickTumbler.generated.h"

UCLASS()
class KMEPROJECT_API AKMEProjectLockpickTumbler : public AActor
{
	GENERATED_BODY()
	
//	UPROPERTY(EditAnywhere, Category = Mesh)
//	class USkeletalMeshComponent* MeshTumbler;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Spring;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* Tumbler;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* SmallTumbler;

public:	
	// Sets default values for this actor's properties
	AKMEProjectLockpickTumbler();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Reference)
	class AKMEProjectLockpickPawn* LockpickPawnRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
	int32 TumblerIndex;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	float TumblerSeed;

	float RandomNumber;

	float TargetTime;

	float TargetTime2;

	bool bCanSeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SeedTime();

	float RandomNumberTest;

	bool bDelay;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
