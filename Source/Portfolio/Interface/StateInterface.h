// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StateInterface.generated.h"

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
	Move,
	CombatReady,
	Combating
};

struct FInputActionValue;

class PORTFOLIO_API IStateInterface
{
	GENERATED_BODY()

public:
	virtual ECreatureState GetState() = 0;

public:
	virtual bool IsTransitable(ECreatureState NewState) = 0;
	virtual void HandleMove(const FVector& Location) = 0;
	virtual void HandleAttack(const FVector& Location) = 0;
};
