// Fill out your copyright notice in the Description page of Project Settings.


#include "State/CombatingState.h"
#include "State/CharacterStateSubsystem.h"
#include "Character/Creature.h"

UCombatingState::UCombatingState()
	: IStateInterface()
{
}

void UCombatingState::ExitState(ACreature* Creature)
{
}

void UCombatingState::EnterState(ACreature* Creature)
{
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Combating"));
	Creature->DefaultAttack();
	StateSubsystem->SetState(Creature, ECreatureState::CombatReady);
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
	// Can't Move While Combating
}

void UCombatingState::HandleMoveWithDirection(
	ACreature* Creature, 
	ADefaultPlayerController* Controller, 
	const FVector& Direction
)
{
	// Can't Move While Combating
}

void UCombatingState::HandleAttack(
	ACreature* Creature,
	ADefaultPlayerController* Controller,
	ACreature* Target
)
{
	// Can't Double Attack
}
