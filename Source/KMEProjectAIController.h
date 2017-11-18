// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "KMEProjectAIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

/**
 * 
 */
UCLASS()
class KMEPROJECT_API AKMEProjectAIController : public AAIController
{
	GENERATED_BODY()

public:

	AKMEProjectAIController();

	virtual void Possess(class APawn* InPawn) override;

	//AKMEProjectAIController(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

	/* Cached BT component */
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorComp;	

protected:

	int32 GetPlayerKeyID;
};
