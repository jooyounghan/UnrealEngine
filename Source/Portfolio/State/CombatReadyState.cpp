// Fill out your copyright notice in the Description page of Project Settings.

#include "State/CombatReadyState.h"
#include "Character/Creature.h"
#include "System/DefaultGameInstance.h"
#include "State/CharacterStateSubsystem.h"

UCombatReadyState::UCombatReadyState()
	: IStateInterface()
{
}

void UCombatReadyState::ExitState(ACreature* Creature)
{
	FTimerManager& WorldTimerManager = Creature->GetWorldTimerManager();
	WorldTimerManager.ClearTimer(ToIdleTimerHandle);
}

void UCombatReadyState::EnterState(ACreature* Creature)
{

	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Combat Ready"));
	Creature->GetWorldTimerManager().ClearTimer(ToIdleTimerHandle);

	ToIdleDelegate = FTimerDelegate::CreateUObject(
		StateSubsystem,
		&UCharacterStateSubsystem::SetState,
		Creature, ECreatureState::Idle
	);

	Creature->GetWorldTimerManager().SetTimer(ToIdleTimerHandle, ToIdleDelegate, 10.f, true);
}

ECreatureState UCombatReadyState::GetState()
{
	return ECreatureState::CombatReady;
}

bool UCombatReadyState::IsTransitable(ECreatureState NewState)
{
	return NewState == 
		ECreatureState::CombatReady 
		|| NewState == ECreatureState::Combating 
		|| NewState ==ECreatureState::Idle;
}

void UCombatReadyState::HandleMove(
	ACreature* Creature, 
	ADefaultPlayerController* Controller,
	const FVector2D& Movement, 
	const FVector& ForwardVector, 
	const FVector& RightVector
)
{
	DefaultHandleMove(Creature, Controller, Movement, ForwardVector, RightVector);
}

void UCombatReadyState::HandleMoveWithDirection(
	ACreature* Creature, 
	ADefaultPlayerController* Controller,
	const FVector& Direction
)
{
	DefaultHandleMove(Creature, Controller, Direction);
}

void UCombatReadyState::HandleAttack(
	ACreature* Creature,
	ADefaultPlayerController* Controller,
	ACreature* Target
)
{
	Target ? Creature->SetTargetToAttack(Target) : Creature->ResetTargetToAttack();

	if (Creature->IsNearForAttacking())
	{
		StateSubsystem->SetState(Creature, ECreatureState::Combating);
	}
}
