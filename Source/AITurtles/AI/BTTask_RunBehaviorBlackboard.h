// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BehaviorTree/Tasks/BTTask_RunBehavior.h"
#include "BTTask_RunBehaviorBlackboard.generated.h"

UCLASS()
class AITURTLES_API UBTTask_RunBehaviorBlackboard : public UBTTask_RunBehavior
{
	GENERATED_UCLASS_BODY()

	/** initialize any asset related data */
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	/** get name of selected blackboard key */
	FORCEINLINE FName GetSelectedBlackboardKey() const { return BlackboardKey.SelectedKeyName; }
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category=Blackboard)
	struct FBlackboardKeySelector BlackboardKey;
};
