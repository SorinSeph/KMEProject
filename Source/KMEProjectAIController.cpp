// Fill out your copyright notice in the Description page of Project Settings.

#include "KMEProjectAIController.h"
#include "KMEProjectEnemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Engine.h"

AKMEProjectAIController::AKMEProjectAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));

	BrainComponent = BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));

}

void AKMEProjectAIController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);

	AKMEProjectEnemy* EnemyBot = Cast<AKMEProjectEnemy>(InPawn);

	if (EnemyBot && EnemyBot->EnemyBehavior)
	{
		if (EnemyBot->EnemyBehavior->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*EnemyBot->EnemyBehavior->BlackboardAsset);
		}

		BehaviorComp->StartTree(*(EnemyBot->EnemyBehavior));
	}


	//	if (EnemyBot->BotBehavior->BlackboardAsset)
	//	{
	//		BlackboardComp->InitializeBlackboard(*EnemyBot->BotBehavior->BlackboardAsset);
	//	}

	//	else
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("EnemyBot->BotBehavior->BlackboardAsset failed"));
	//	}

	//	EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
	//	NeedAmmoKeyID = BlackboardComp->GetKeyID("NeedAmmo");

	//BehaviorComp->StartTree(*(EnemyBot->EnemyBehavior));
	
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("On possess called!"));
}
