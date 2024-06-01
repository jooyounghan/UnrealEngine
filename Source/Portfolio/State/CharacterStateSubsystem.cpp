// Fill out your copyright notice in the Description page of Project Settings.


#include "State/CharacterStateSubsystem.h"

#include "Log/LogChannel.h"
#include "Character/Creature.h"

#include "State/IdleState.h"
#include "State/CombatReadyState.h"
#include "State/CombatingState.h"
#include "State/CharacterStateSubsystem.h"

void UCharacterStateSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogStateLoad, Log, TEXT("State Subsystem Initialized"));

	StateEnumToClass.Add(ECreatureState::Idle, NewObject<UIdleState>(this));
	StateEnumToClass.Add(ECreatureState::CombatReady, NewObject<UCombatReadyState>(this));
	StateEnumToClass.Add(ECreatureState::Combating, NewObject<UCombatingState>(this));
}

void UCharacterStateSubsystem::Deinitialize()
{
}

void UCharacterStateSubsystem::SetState(ACreature* Creature, ECreatureState NewStateID)
{
	if (Creature)
	{
		TScriptInterface<IStateInterface>* NewStatePtr = StateEnumToClass.Find(NewStateID);

		if (NewStatePtr)
		{
			IStateInterface* NewState = NewStatePtr->GetInterface();
			IStateInterface* CurrentState = Creature->CharacterState;
			if (CurrentState)
			{
				if (CurrentState->IsTransitable(NewStateID))
				{
					CurrentState->ExitState(Creature);
					NewState->EnterState(Creature);
					Creature->CharacterState = NewState;
				}
			}
			else
			{
				Creature->CharacterState = NewState;
			}
		}
	}
}