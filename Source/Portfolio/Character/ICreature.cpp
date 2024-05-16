// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ICreature.h"

// Sets default values
AICreature::AICreature()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AICreature::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AICreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AICreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

