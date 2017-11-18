// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"
#include "KMEProjectEnemy.generated.h"

UCLASS()
class KMEPROJECT_API AKMEProjectEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKMEProjectEnemy();

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* EnemyMesh;

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* EnemyBehavior;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

//	UPROPERTY(VisibleAnywhere, Category = AI)
//	class UAIPerceptionComponent* AIPerception;

//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
//	class UAISenseConfig_Sight* AISight;

//	UFUNCTION()
//	void OnPerceivedMessage(TArray<AActor*> testActors);

//	UFUNCTION()
//	void OnPerceptionUpdatedMessage(AActor* Actor, FAIStimulus Stimulus);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
