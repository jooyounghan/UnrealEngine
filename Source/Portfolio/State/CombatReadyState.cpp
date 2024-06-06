// Fill out your copyright notice in the Description page of Project Settings.

#include "State/CombatReadyState.h"
#include "State/CharacterStateSubsystem.h"

#include "Character/Creature.h"

#include "System/DefaultGameInstance.h"

#include "Controller/DefaultPlayerController.h"

#include "Util/DefaultGamePlayTags.h"

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

void UCombatReadyState::HandleKeyMove(
	ACreature* Creature, 
	ADefaultPlayerController* Controller,
	const FVector2D& Movement, 
	const FVector& ForwardVector, 
	const FVector& RightVector
)
{
	DefaultHandleKeyMove(Creature, Controller, Movement, ForwardVector, RightVector);
}

void UCombatReadyState::HandleMouseClickingMove(
	ACreature* Creature, 
	ADefaultPlayerController* Controller
)
{
	IStateInterface::DefaultHandleMouseClickingMove(Creature, Controller);
}

void UCombatReadyState::HandleMouseClickMove(
	ACreature* Creature, 
	ADefaultPlayerController* Controller, 
	UNiagaraSystem* ClickFX
)
{
	IStateInterface::DefaultHandleMouseClickMove(Creature, Controller, ClickFX);
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

void UCombatReadyState::HandleChase(ACreature* Creature)
{
	ACreature* Target = Creature->GetTargetToAttack();
	if (Target)
	{
		if (Creature->IsNearForAttacking())
		{
			StateSubsystem->SetState(Creature, ECreatureState::Combating);
		}
		else
		{
			const FVector Direction = (Target->GetActorLocation() - Creature->GetActorLocation()).GetSafeNormal();
			Creature->AddMovementInput(Direction);
		}
	}
}

void UCombatReadyState::HandleGamePlayEvent(ACreature* Creature, FGameplayTag EventTag)
{
}
