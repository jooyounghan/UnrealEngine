#include "State/CombatingState.h"
#include "State/CharacterStateSubsystem.h"

#include "Character/Creature.h"

#include "Util/DefaultGamePlayTags.h"

UCombatingState::UCombatingState()
	: IStateInterface()
{
}

void UCombatingState::ExitState(ACreature* Creature)
{
}

void UCombatingState::EnterState(ACreature* Creature)
{
	Creature->DefaultAttack();
}

ECreatureState UCombatingState::GetState()
{
	return ECreatureState::Combating;
}

bool UCombatingState::IsTransitable(ECreatureState NewState)
{
	return NewState == ECreatureState::CombatReady;
}

void UCombatingState::HandleKeyMove(
	ACreature* Creature, 
	ADefaultPlayerController* Controller,
	const FVector2D& Movement,
	const FVector& ForwardVector, 
	const FVector& RightVector
)
{
	// Can't Move While Combating
}

void UCombatingState::HandleMouseClickingMove(
	ACreature* Creature, 
	ADefaultPlayerController* Controller
)
{
	// Can't Move While Combating
}

void UCombatingState::HandleMouseClickMove(
	ACreature* Creature, 
	ADefaultPlayerController* Controller, 
	UNiagaraSystem* ClickFX
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

void UCombatingState::HandleChase(ACreature* Creature)
{
	// Can't Chase
}

void UCombatingState::HandleGamePlayEvent(ACreature* Creature, FGameplayTag EventTag)
{
	if (EventTag.MatchesTag(GamePlayTags::InputAttackEnd))
	{
		Creature->ResetTargetToAttack();
		StateSubsystem->SetState(Creature, ECreatureState::CombatReady);
	}
}
