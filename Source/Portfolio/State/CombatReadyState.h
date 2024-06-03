// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interface/StateInterface.h"
#include "CombatReadyState.generated.h"

UCLASS()
class PORTFOLIO_API UCombatReadyState : public UObject, public IStateInterface
{
	GENERATED_BODY()

private:
	UCombatReadyState();

protected:
	FTimerHandle ToIdleTimerHandle;

protected:
	FTimerDelegate ToIdleDelegate;

public:
	virtual void ExitState(ACreature* Creature) override;	
	virtual void EnterState(ACreature* Creature) override;

public:
	virtual ECreatureState GetState() override;

public:
	virtual bool IsTransitable(ECreatureState NewState) override;

public:
	virtual void HandleMove(
		ACreature* Creature,
		ADefaultPlayerController* Controller,
		const FVector2D& Movement,
		const FVector& ForwardVector,
		const FVector& RightVector
	) override;

	virtual void HandleMoveWithDirection(
		ACreature* Creature, 
		ADefaultPlayerController* Controller,
		const FVector& Direction
	) override;

public:
	virtual void HandleAttack(
		ACreature* Creature,
		ADefaultPlayerController* Controller,
		ACreature* Target
	) override;
};
