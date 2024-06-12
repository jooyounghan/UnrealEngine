// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UnitEnemy.h"
#include "Components/CapsuleComponent.h"


AUnitEnemy::AUnitEnemy()
{
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	if (CapsuleComp != nullptr)
	{
		CapsuleComp->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
		//CapsuleComp->SetCollisionProfileName(TEXT("Enemy"));
		CapsuleComp->UpdateCollisionProfile();
	}
}

void AUnitEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AUnitEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnitEnemy::Target()
{
	Super::Target();
}

void AUnitEnemy::UnTarget()
{
	Super::UnTarget();
}
