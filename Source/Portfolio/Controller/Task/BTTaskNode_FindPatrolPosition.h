// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FindPatrolPosition.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UBTTaskNode_FindPatrolPosition : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_FindPatrolPosition();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector PatrolPositionKey;
};
