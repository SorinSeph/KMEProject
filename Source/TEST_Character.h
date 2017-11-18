// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"
#include "TEST_Character.generated.h"

UCLASS()
class KMEPROJECT3_API ATEST_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATEST_Character();

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* CharBehavior;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = AI)
	class UAIPerceptionComponent* AIPerception;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	class UAISenseConfig_Sight* AISight;

	UFUNCTION()
	void OnPerceivedMessage(TArray<AActor*> testActors);

	UFUNCTION()
	void OnPerceptionUpdatedMessage(AActor* Actor, FAIStimulus Stimulus);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
