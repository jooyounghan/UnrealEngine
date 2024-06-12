#include "Controller/Task/BTTaskNode_FindPatrolPosition.h"
#include "Controller/DefaultAIController.h"
#include "Character/Creature.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_FindPatrolPosition::UBTTaskNode_FindPatrolPosition()
{
	NodeName = TEXT("Find Patrol Position");
}

EBTNodeResult::Type UBTTaskNode_FindPatrolPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACreature* Creature = Cast<ACreature>(OwnerComp.GetAIOwner()->GetPawn());
	if (Creature)
	{
		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(Creature->GetWorld());

		FNavLocation NavLocation;
		if (NavSystem->GetRandomPointInNavigableRadius(Creature->GetActorLocation(), 500.f, NavLocation))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(PatrolPositionKey.SelectedKeyName, NavLocation.Location);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
