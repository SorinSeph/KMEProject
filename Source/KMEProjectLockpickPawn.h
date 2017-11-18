// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "KMEProjectPlayerController.h"
#include "KMEProjectLockpickTumbler.h"
#include "Engine.h"
#include "KMEProjectLockpickPawn.generated.h"


UCLASS()
class KMEPROJECT_API AKMEProjectLockpickPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Camera)
	class UCameraComponent* LockpickCamera;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* Lockpick;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Tumbler2;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Tumbler3;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Tumbler4;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Lock;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	int32 NumberOfTumblers;

	UPROPERTY(EditAnywhere, Category = Reference)
	TArray<class AKMEProjectLockpickTumbler*> TumblerRef;

	UPROPERTY(EditAnywhere, Category = Reference)
	TArray<TSubclassOf<class AKMEProjectLockpickTumbler>> TumblerRef2;

	UPROPERTY(EditAnywhere, Category = Mesh)
	TArray <class UBillboardComponent*> SpawnLocArray;

	class AKMEProjectPlayerController* MyPC;

	bool bDelay;

	float LockpickPosition;

	float TargetTime;

public:
	// Sets default values for this pawn's properties
	AKMEProjectLockpickPawn();

	UPROPERTY(EditAnywhere, Category = Gameplay)
	int32 LockpickID;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	class USkeletalMeshComponent* Tumbler1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = Mesh)
	class USkeletalMeshComponent* Spring;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	TArray<class USkeletalMeshComponent*> TumblerArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	TArray<class UStaticMeshComponent*> TumblerArrayStatic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	TArray<TSubclassOf<USkeletalMeshComponent>> TumblerSubclassArray;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	class UBillboardComponent* TumblerSpawnLoc;

	class USkeletalMeshComponent* Tumbler = Cast<USkeletalMeshComponent>(StaticLoadObject(USkeletalMeshComponent::StaticClass(), NULL, TEXT("/Game/FirstPersonCPP/Blueprints/Lockpick/Tumblers/tumbler1.tumbler1")));

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	float MorphSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	float MorphSpeed2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	float MorphSpeed3;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	float MorphSpeed4;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	float MorphSpeed5;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	float MorphSpeed6;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	float MorphSpeed7;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	float MorphSpeed8;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	bool bWantsToLockpick;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	int32 LockpickIndex;

	float CurrentTime;

	float CurrentMousePosX;
	float CurrentMousePosY;

	float OriginalMousePosX;
	float OriginalMousePosY;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void StartLockpick();

	void EndLockpick();

	void SpawnTumblers();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	
};
