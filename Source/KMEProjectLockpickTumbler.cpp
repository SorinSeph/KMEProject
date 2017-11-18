// Fill out your copyright notice in the Description page of Project Settings.

#include "KMEProjectLockpickTumbler.h"
#include "Engine.h"


// Sets default values
AKMEProjectLockpickTumbler::AKMEProjectLockpickTumbler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spring = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SpringMesh"));

	Tumbler = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TumblerMesh"));

	SmallTumbler = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SmallTumbler"));

//	MeshTumbler = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshforTumbler"));

	bCanSeed = false;

	TargetTime = 0;
	RandomNumberTest = 0;
	TumblerIndex = 0;
	TumblerSeed = 1;
	RandomNumber = FMath::FRandRange(0.2, 0.85);
	TargetTime2 = 10;

}

void AKMEProjectLockpickTumbler::SeedTime()
{

}

// Called when the game starts or when spawned
void AKMEProjectLockpickTumbler::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKMEProjectLockpickTumbler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LockpickPawnRef->bWantsToLockpick)
	{

		if (FMath::IsNearlyEqual(GetWorld()->GetTimeSeconds(), TargetTime2, 0.1f))
		{
			bCanSeed = true;
			//MorphSpeed = FMath::FInterpConstantTo(MorphSpeed, FMath::FRandRange(-2, 1), GetWorld()->GetDeltaSeconds(), 1);
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(MorphSpeed));
		}

		if (bCanSeed)
		{
			TumblerSeed = FMath::FRandRange(-0.3f, 0.3f);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Achieved!"));
		}
	}
	else
	{
		TumblerSeed = 1;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::SanitizeFloat(RandomNumber));
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::SanitizeFloat(GetWorld()->GetTimeSeconds()));
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(GetWorld()->GetTimeSeconds()));
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(TargetTime2));

}
