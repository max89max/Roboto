// Fill out your copyright notice in the Description page of Project Settings.

#include "BuddyAiController.h"
/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "BuddyAi.h"


ABuddyAiController::ABuddyAiController(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	/* Match with the AI/ZombieBlackboard */
	/*PatrolLocationKeyName = "PatrolLocation";
	CurrentWaypointKeyName = "CurrentWaypoint";
	BotTypeKeyName = "BotType";
	TargetEnemyKeyName = "TargetEnemy";*/

	/* Initializes PlayerState so we can assign a team index to AI */
	//bWantsPlayerState = true;
}

void ABuddyAiController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);

	ABuddyAi* dogBot = Cast<ABuddyAI>(InPawn);
	if (dogBot)
	{
		if (dogBot->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*dogBot->BehaviorTree->BlackboardAsset);

			/* Make sure the Blackboard has the type of bot we possessed */
			//SetBlackboardBotType(dogBot->BotType);
		}

		BehaviorComp->StartTree(*dogBot->BehaviorTree);
	}
}


void ABuddyAiController::UnPossess()
{
	Super::UnPossess();

	/* Stop any behavior running as we no longer have a pawn to control */
	BehaviorComp->StopTree();
}


/*void ABuddyAiController::SetWaypoint(ASBotWaypoint* NewWaypoint)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(CurrentWaypointKeyName, NewWaypoint);
	}
}


void ABuddyAiController::SetTargetEnemy(APawn* NewTarget)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(TargetEnemyKeyName, NewTarget);
	}
}


ASBotWaypoint* ABuddyAiController::GetWaypoint()
{
	if (BlackboardComp)
	{
		return Cast<ASBotWaypoint>(BlackboardComp->GetValueAsObject(CurrentWaypointKeyName));
	}

	return nullptr;
}


ASBaseCharacter* ABuddyAiController::GetTargetEnemy()
{
	if (BlackboardComp)
	{
		return Cast<ASBaseCharacter>(BlackboardComp->GetValueAsObject(TargetEnemyKeyName));
	}

	return nullptr;
}


void ABuddyAiController::SetBlackboardBotType(EBotBehaviorType NewType)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsEnum(BotTypeKeyName, (uint8)NewType);
	}
}*/


