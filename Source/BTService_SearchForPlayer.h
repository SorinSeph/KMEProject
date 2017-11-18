// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_SearchForPlayer.generated.h"

/**
 * 
 */
UCLASS()
class KMEPROJECT_API UBTService_SearchForPlayer : public UBTService_BlueprintBase
{
	GENERATED_BODY()
	
public:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
