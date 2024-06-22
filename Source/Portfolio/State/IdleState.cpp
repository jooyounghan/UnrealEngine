// Fill out your copyright notice in the Description page of Project Settings.

#include "IdleState.h"
#include "State/CharacterStateSubsystem.h"

#include "Character/Creature.h"

#include "Util/DefaultGamePlayTags.h"

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
}

ECreatureState UIdleState::GetState()
{
	return ECreatureState::Idle;
}

bool UIdleState::IsTransitable(ECreatureState NewState)
{
	return NewState == ECreatureState::CombatReady;
}

void UIdleState::HandleKeyMove(
	AUnitPlayer* UnitPlayer,
	ADefaultPlayerController* Controller,
	const FVector2D& Movement
)
{
	DefaultHandleKeyMove(UnitPlayer, Controller, Movement);
}

void UIdleState::HandleMouseClickingMove(
	AUnitPlayer* UnitPlayer,
	ADefaultPlayerController* Controller
)
{
	IStateInterface::DefaultHandleMouseClickingMove(UnitPlayer, Controller);
}

void UIdleState::HandleMouseClickMove(
	ADefaultPlayerController* Controller,
	UNiagaraSystem* ClickFX
)
{
	IStateInterface::DefaultHandleMouseClickMove(Controller, ClickFX);
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

void UIdleState::HandleChase(ACreature* Creature)
{
	// Do Nothing 
}

void UIdleState::HandleGamePlayEvent(ACreature* Creature, FGameplayTag EventTag)
{
}
