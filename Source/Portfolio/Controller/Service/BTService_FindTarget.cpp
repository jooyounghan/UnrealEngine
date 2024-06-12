// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/Service/BTService_FindTarget.h"
#include "Character/UnitPlayer.h"
#include "Log/LogChannel.h"
#include "Engine/OverlapResult.h"
#include "Controller/DefaultAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_FindTarget::UBTService_FindTarget()
{
	NodeName = TEXT("Find Target");
	Interval = 0.5f;
}

void UBTService_FindTarget::TickNode(
	UBehaviorTreeComponent& OwnerComp, 
	uint8* NodeMemory, 
	float DeltaSeconds
)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACreature* Creature = Cast<ACreature>(OwnerComp.GetAIOwner()->GetPawn());
	if (Creature == nullptr)
	{
		UE_LOG(LogLocalVariableNull, Fatal, TEXT("Get Creature From Find Target Service Failed"));
		return;
	}

	UWorld* World = Creature->GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogLocalVariableNull, Fatal, TEXT("Get World From Find Target Service Failed"));
		return;
	}

	TArray<FOverlapResult> OutOverlaps;
	bool bResult = World->OverlapMultiByChannel(
		OutOverlaps,
		Creature->GetActorLocation(),
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(300.f)
	);

	if (bResult)
	{
		float TargetDistance = 1E9;
		AUnitPlayer* TargetPlayer = nullptr;
		for (FOverlapResult& Overlap : OutOverlaps)
		{
			AUnitPlayer* TempPlayer = Cast<AUnitPlayer>(Overlap.GetActor());
			if (TempPlayer)
			{
				const float TempTargetDistance = TempPlayer->GetDistanceTo(Creature);
				if (TargetDistance > TempTargetDistance)
				{
					TargetDistance = TempTargetDistance;
					TargetPlayer = TempPlayer;
				}
			}
		}
		
		DrawDebugSphere(World, Creature->GetActorLocation(), 300.f, 16, TargetPlayer != nullptr ? FColor::Green : FColor::Red, false, 0.2f);
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey.SelectedKeyName, TargetPlayer);
	}
}
