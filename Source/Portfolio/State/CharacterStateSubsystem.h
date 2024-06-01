// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interface/StateInterface.h"
#include "CharacterStateSubsystem.generated.h"

class ACreature;

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UCharacterStateSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
protected:
	UPROPERTY()
	TMap<ECreatureState, TScriptInterface<IStateInterface>> StateEnumToClass;

public:
	void SetState(ACreature* Creature, ECreatureState NewStateID);
};
