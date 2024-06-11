// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DefaultAIController.h"

ADefaultAIController::ADefaultAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ADefaultAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ADefaultAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
