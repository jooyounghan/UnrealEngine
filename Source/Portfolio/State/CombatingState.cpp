// Fill out your copyright notice in the Description page of Project Settings.


#include "State/CombatingState.h"
#include "State/CharacterStateSubsystem.h"


UCombatingState::UCombatingState()
	: IStateInterface()
{
}

void UCombatingState::ExitState(ACreature* Creature)
{
}

void UCombatingState::EnterState(ACreature* Creature)
{
}

ECreatureState UCombatingState::GetState()
{
	return ECreatureState::Combating;
}

bool UCombatingState::IsTransitable(ECreatureState NewState)
{
	return NewState == ECreatureState::CombatReady;
}

void UCombatingState::HandleMove(
	ACreature* Creature, 
	ADefaultPlayerController* Controller,
	const FVector2D& Movement,
	const FVector& ForwardVector, 
	const FVector& RightVector
)
{
	DefaultHandleMove(Creature, Controller, Movement, ForwardVector, RightVector);
}

void UCombatingState::HandleMoveWithDirection(
	ACreature* Creature, 
	ADefaultPlayerController* Controller, 
	const FVector& Direction
)
{
	DefaultHandleMove(Creature, Controller, Direction);
}

void UCombatingState::HandleAttack(
	ACreature* Creature,
	ADefaultPlayerController* Controller
)
{
}
