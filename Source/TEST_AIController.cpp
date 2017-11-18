// Fill out your copyright notice in the Description page of Project Settings.

#include "TEST_AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Engine.h"
#include "TEST_Character.h"

ATEST_AIController::ATEST_AIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));

	BrainComponent = BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}

void ATEST_AIController::Possess(class APawn* InPawn)

{
	Super::Possess(InPawn);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("OnPossess called."));

	ATEST_Character* BotChar = Cast<ATEST_Character>(InPawn);

	if (BotChar && BotChar->CharBehavior)
	{
		if (BotChar->CharBehavior->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*BotChar->CharBehavior->BlackboardAsset);
		}

		BehaviorComp->StartTree(*(BotChar->CharBehavior));
	}
}