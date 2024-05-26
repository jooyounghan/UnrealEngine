// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Creature.h"
#include "UnitEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AUnitEnemy : public ACreature
{
	GENERATED_BODY()
	
public:
	AUnitEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Target() override;
	virtual void UnTarget() override;
};
