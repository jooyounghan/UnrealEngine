// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StateInterface.generated.h"

class ACreature;
class ADefaultPlayerController;
class UCharacterStateSubsystem;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStateInterface : public UInterface
{
	GENERATED_BODY()
};

UENUM(BlueprintType)
enum class ECreatureState : uint8
{
	Idle,
	CombatReady,
	Combating
};

struct FInputActionValue;
struct FGameplayTag;

class PORTFOLIO_API IStateInterface
{
	GENERATED_BODY()

protected:
	UCharacterStateSubsystem* StateSubsystem;

public:
	inline void SetStateSubsystem(UCharacterStateSubsystem* StateSubsystemIn) { StateSubsystem = StateSubsystemIn; }

public:
	virtual ECreatureState GetState() = 0;

public:
	virtual bool IsTransitable(ECreatureState NewState) = 0;

public:
	virtual void ExitState(ACreature* Creature) = 0;

	virtual void EnterState(ACreature* Creature) = 0;

public:
	virtual void HandleMove(
		ACreature* Creature,
		ADefaultPlayerController* Controller,
		const FVector2D& Movement,
		const FVector& ForwardVector,
		const FVector& RightVector
	) = 0;

	virtual void HandleMoveWithDirection(
		ACreature* Creature, 
		ADefaultPlayerController* Controller, 
		const FVector& Direction
	) = 0;

	virtual void HandleAttack(
		ACreature* Creature,
		ADefaultPlayerController* Controller,
		ACreature* Target
	) = 0;

	virtual void HandleChase(ACreature* Creature) = 0;

public:
	virtual void HandleGamePlayEvent(ACreature* Creature, FGameplayTag EventTag) = 0;

public:
	void DefaultHandleMove(
		ACreature* Creature,
		ADefaultPlayerController* Controller,
		const FVector2D& Movement,
		const FVector& ForwardVector,
		const FVector& RightVector
	);
public:
	void DefaultHandleMove(
		ACreature* Creature, 
		ADefaultPlayerController* Controller,
		const FVector& Direction
	);
};
