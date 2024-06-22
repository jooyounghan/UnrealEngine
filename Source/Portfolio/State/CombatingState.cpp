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
	DefaultAttack(Creature);
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
	AUnitPlayer* UnitPlayer,
	ADefaultPlayerController* Controller,
	const FVector2D& Movement
)
{
	// Can't Move While Combating
}

void UCombatingState::HandleMouseClickingMove(
	AUnitPlayer* UnitPlayer,
	ADefaultPlayerController* Controller
)
{
	// Can't Move While Combating
}

void UCombatingState::HandleMouseClickMove(
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



void UCombatingState::DefaultAttack(ACreature* Creature)
{
	UAnimMontage* AttackAnimMontage = Creature->AttackAnimMontage;
	if (AttackAnimMontage)
	{
		const FString AttackFormatter = FString(TEXT("Attack_{0}"));
		const FString AttackFormatted = FString::Format(*AttackFormatter, { rand() % AttackAnimMontage->GetNumSections() });
		Creature->PlayAnimMontage(AttackAnimMontage, 1.0f, *AttackFormatted);
	}
}