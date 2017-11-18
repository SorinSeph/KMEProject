// Fill out your copyright notice in the Description page of Project Settings.

#include "KMEProjectEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "KMEProjectAIController.h"
#include "Engine.h"


// Sets default values
AKMEProjectEnemy::AKMEProjectEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshofEnemy"));
	EnemyMesh->SetupAttachment(GetCapsuleComponent());

	/*AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	AISight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Sense"));
	AIPerception->ConfigureSense(*AISight);
	AIPerception->SetDominantSense(AISight->GetSenseImplementation());
	//AIPerception->OnPerceptionUpdated.AddDynamic(this, &AKMEProjectEnemy::OnPerceivedMessage);
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AKMEProjectEnemy::OnPerceptionUpdatedMessage);
	

	AISight->PeripheralVisionAngleDegrees = 30.0f;
	AISight->SightRadius = 1000.0f;
	AISight->LoseSightRadius = 1200.0f;
	AISight->DetectionByAffiliation.bDetectEnemies = true;
	AISight->DetectionByAffiliation.bDetectNeutrals = true;
	AISight->DetectionByAffiliation.bDetectFriendlies = true;*/

}

// Called when the game starts or when spawned
void AKMEProjectEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

/*
void AKMEProjectEnemy::OnPerceivedMessage(TArray<AActor*> testActors)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("OnPerceptionUpdated called."));
}

void AKMEProjectEnemy::OnPerceptionUpdatedMessage(AActor* Actor, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("OnTargetPerceptionUpdated called."));
}*/

// Called every frame
void AKMEProjectEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKMEProjectEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

