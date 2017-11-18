// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TEST_AIController.generated.h"

/**
 * 
 */
UCLASS()
class KMEPROJECT_API ATEST_AIController : public AAIController
{
	GENERATED_BODY()
	
public:

	ATEST_AIController();

	virtual void Possess(class APawn* InPawn) override;
	
private:

	UPROPERTY()
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY()
	class UBehaviorTreeComponent* BehaviorComp;


};
