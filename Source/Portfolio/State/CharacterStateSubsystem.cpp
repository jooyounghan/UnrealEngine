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
	StateEnumToName.Add(ECreatureState::Idle, FString(TEXT("Idle")));
	StateEnumToName.Add(ECreatureState::CombatReady, FString(TEXT("Combat Ready")));
	StateEnumToName.Add(ECreatureState::Combating, FString(TEXT("Combating")));

	StateEnumToClass.Add(ECreatureState::Idle, NewObject<UIdleState>(this));
	StateEnumToClass.Add(ECreatureState::CombatReady, NewObject<UCombatReadyState>(this));
	StateEnumToClass.Add(ECreatureState::Combating, NewObject<UCombatingState>(this));

	for (auto& StateElem : StateEnumToClass)
	{
		StateElem.Value->SetStateSubsystem(this);
	}
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
			TScriptInterface<IStateInterface> NewState = *NewStatePtr;
			TScriptInterface<IStateInterface> CurrentState = Creature->CharacterState;
			if (CurrentState)
			{
				if (CurrentState->IsTransitable(NewStateID))
				{
					UE_LOG(LogStateChange, Log, TEXT("State Changed %s -> %s"), *StateEnumToName[CurrentState->GetState()], *StateEnumToName[NewState->GetState()]);

					CurrentState->ExitState(Creature);
					Creature->CharacterState = NewState;
					NewState->EnterState(Creature);
				}
			}
			else
			{
				Creature->CharacterState = NewState;
			}
		}
	}
}