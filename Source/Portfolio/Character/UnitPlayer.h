// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Creature.h"
#include "UnitPlayer.generated.h"

UCLASS()
class PORTFOLIO_API AUnitPlayer : public ACreature
{
	GENERATED_BODY()
	
public:
	AUnitPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	void ShowTargeted();
};
