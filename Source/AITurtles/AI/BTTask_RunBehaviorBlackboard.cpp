// Copyright Epic Games, Inc. All Rights Reserved.

#include "BTTask_RunBehaviorBlackboard.h"
#include "VisualLogger/VisualLogger.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTTask_RunBehaviorBlackboard::UBTTask_RunBehaviorBlackboard(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_RunBehaviorBlackboard, BlackboardKey), UBehaviorTree::StaticClass());
	NodeName = "Run Behavior Blackboard";
}

void UBTTask_RunBehaviorBlackboard::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (BBAsset)
	{
		BlackboardKey.ResolveSelectedKey(*BBAsset);
	}
	else
	{
		UE_LOG(LogBehaviorTree, Warning, TEXT("Can't initialize task: %s, make sure that behavior tree specifies blackboard asset!"), *GetName());
	}
}

EBTNodeResult::Type UBTTask_RunBehaviorBlackboard::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	if (UObject* KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID()))
	{
		if (UBehaviorTree* TargetBehaviorTree = Cast<UBehaviorTree>(KeyValue))
		{
			BehaviorAsset = TargetBehaviorTree;
			return Super::ExecuteTask(OwnerComp, NodeMemory);
		}
	}
	return EBTNodeResult::Failed;
}