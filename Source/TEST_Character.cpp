// Fill out your copyright notice in the Description page of Project Settings.

#include "TEST_Character.h"
#include "TEST_AIController.h"
#include "Perception/AIPerceptionComponent.h"


// Sets default values
ATEST_Character::ATEST_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	AISight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Sense"));
	AIPerception->ConfigureSense(*AISight);
	AIPerception->SetDominantSense(AISight->GetSenseImplementation());
	AIPerception->OnPerceptionUpdated.AddDynamic(this, &ATEST_Character::OnPerceivedMessage);
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ATEST_Character::OnPerceptionUpdatedMessage);


	AISight->PeripheralVisionAngleDegrees = 30.0f;
	AISight->SightRadius = 1000.0f;
	AISight->LoseSightRadius = 1200.0f;
	AISight->DetectionByAffiliation.bDetectEnemies = true;
	AISight->DetectionByAffiliation.bDetectNeutrals = true;
	AISight->DetectionByAffiliation.bDetectFriendlies = true;
}

// Called when the game starts or when spawned
void ATEST_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATEST_Character::OnPerceivedMessage(TArray<AActor*> testActors)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("OnPerceptionUpdated called."));
}

void ATEST_Character::OnPerceptionUpdatedMessage(AActor* Actor, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("OnTargetPerceptionUpdated called."));
}

// Called every frame
void ATEST_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATEST_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

