// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"

#include "DefaultAssetManager.h"
#include "Data/InputDataAsset.h"
#include "DefaultGamePlayTags.h"

ADefaultPlayerController::ADefaultPlayerController(const FObjectInitializer& ObjectInitializer)
	: APlayerController(ObjectInitializer)
{

}

void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (const UInputDataAsset* InputData = UDefaultAssetManager::GetAssetByAssetTag<UInputDataAsset>(GamePlayTags::InputAction))
	{
		if (auto* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(InputData->InputMappingContext, 0);
		}
	}
}

void ADefaultPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (const UInputDataAsset* InputData = UDefaultAssetManager::GetAssetByAssetTag<UInputDataAsset>(GamePlayTags::InputAction))
	{
		if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			auto InputActioinMove = InputData->FindInputActionByTag(GamePlayTags::InputActionMove);
			auto InputActioinTurn = InputData->FindInputActionByTag(GamePlayTags::InputActionTurn);
			EnhancedInputComponent->BindAction(InputActioinMove, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
			EnhancedInputComponent->BindAction(InputActioinTurn, ETriggerEvent::Triggered, this, &ThisClass::InputTurn);
		}
	}
}

void ADefaultPlayerController::InputMove(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();
	MovementVector.Normalize();

	FRotator Rotator = GetControlRotation();
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0, Rotator.Yaw, 0));
	FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));

	GetPawn()->AddMovementInput(ForwardVector, MovementVector.X);
	GetPawn()->AddMovementInput(RightVector, MovementVector.Y);
}

void ADefaultPlayerController::InputTurn(const FInputActionValue& InputValue)
{
	FVector2D AngleVector = InputValue.Get<FVector2D>();
	AddYawInput(AngleVector.X);
	AddPitchInput(AngleVector.Y);

}
