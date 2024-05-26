// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetingInterface.generated.h"

class ACreature;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTargetingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PORTFOLIO_API ITargetingInterface
{
	GENERATED_BODY()

protected:
	bool bIsTargeted = false;

public:
	virtual void Target() = 0;
	virtual void UnTarget() = 0;
};
