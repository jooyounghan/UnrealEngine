// Fill out your copyright notice in the Description page of Project Settings.

#include "IdleState.h"
#include "Character/Creature.h"
#include "State/CharacterStateSubsystem.h"

UIdleState::UIdleState()
	: IStateInterface()
{
}


void UIdleState::ExitState(ACreature* Creature)
{
}

void UIdleState::EnterState(ACreature* Creature)
{
	Creature->ResetTargetToAttack();
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Idle"));
}

ECreatureState UIdleState::GetState()
{
	return ECreatureState::Idle;
}

bool UIdleState::IsTransitable(ECreatureState NewState)
{
	return NewState == ECreatureState::CombatReady;
}

void UIdleState::HandleMove(
	ACreature* Creature,
	ADefaultPlayerController* Controller,
	const FVector2D& Movement, 
	const FVector& ForwardVector, 
	const FVector& RightVector
)
{
	DefaultHandleMove(Creature, Controller, Movement, ForwardVector, RightVector);
}

void UIdleState::HandleMoveWithDirection(
	ACreature* Creature, 
	ADefaultPlayerController* Controller, 
	const FVector& Direction)
{
	DefaultHandleMove(Creature, Controller, Direction);
}

void UIdleState::HandleAttack(
	ACreature* Creature,
	ADefaultPlayerController* Controller,
	ACreature* Target
)
{
	Target ? Creature->SetTargetToAttack(Target) : Creature->ResetTargetToAttack();

	if (Target)
	{
		StateSubsystem->SetState(Creature, ECreatureState::CombatReady);
	}
}
