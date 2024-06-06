// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/UnitPlayer.h"

// Sets default values
AUnitPlayer::AUnitPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUnitPlayer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AUnitPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShowTargeted();
}

// Called to bind functionality to input
void AUnitPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AUnitPlayer::ShowTargeted()
{
	if (TargetToAttack)
	{
		DrawDebugSphere(GetWorld(), TargetToAttack->GetActorLocation(), 150.f, 15, FColor::Magenta);
	}
}
