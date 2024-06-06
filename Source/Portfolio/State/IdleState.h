// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interface/StateInterface.h"
#include "IdleState.generated.h"

UCLASS()
class PORTFOLIO_API UIdleState : public UObject, public IStateInterface
{
	GENERATED_BODY()
	
private:
	UIdleState();

public:
	virtual void ExitState(ACreature* Creature) override;
	virtual void EnterState(ACreature* Creature) override;

public:
	virtual ECreatureState GetState() override;

public:
	virtual bool IsTransitable(ECreatureState NewState) override;

public:
	virtual void HandleKeyMove(
		ACreature* Creature,
		ADefaultPlayerController* Controller,
		const FVector2D& Movement
	) override;

	virtual void HandleMouseClickingMove(
		ACreature* Creature,
		ADefaultPlayerController* Controller
	) override;

	virtual void HandleMouseClickMove(
		ACreature* Creature,
		ADefaultPlayerController* Controller,
		UNiagaraSystem* ClickFX
	) override;

	virtual void HandleAttack(
		ACreature* Creature,
		ADefaultPlayerController* Controller,
		ACreature* Target
	) override;

	virtual void HandleChase(ACreature* Creature) override;

public:
	virtual void HandleGamePlayEvent(ACreature* Creature, FGameplayTag EventTag) override;
};
