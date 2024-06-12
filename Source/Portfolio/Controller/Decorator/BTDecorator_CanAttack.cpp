#include "Controller/Decorator/BTDecorator_CanAttack.h"
#include "Controller/DefaultAIController.h"
#include "Character/Creature.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CanAttack::UBTDecorator_CanAttack()
{
	NodeName = TEXT("Can Attack");
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp, 
	uint8* NodeMemory
) const
{
	ACreature* Creature = Cast<ACreature>(OwnerComp.GetAIOwner()->GetPawn());
	ACreature* Target = Cast<ACreature>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName));

	if (Creature != nullptr && Target != nullptr)
	{
		return Creature->GetDistanceTo(Target) < 100.f;
	}

	return false;
}
