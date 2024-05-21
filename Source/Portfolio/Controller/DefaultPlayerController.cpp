// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DefaultPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"

#include "Data/DefaultAssetManager.h"
#include "Data/Asset/InputDataAsset.h"
#include "Util/DefaultGamePlayTags.h"

#include "Character/IPlayer.h"

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
			auto InputActioinJump = InputData->FindInputActionByTag(GamePlayTags::InputActionJump);
			auto InputActioinAttack = InputData->FindInputActionByTag(GamePlayTags::InputActionAttack);
			EnhancedInputComponent->BindAction(InputActioinMove, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
			EnhancedInputComponent->BindAction(InputActioinTurn, ETriggerEvent::Triggered, this, &ThisClass::InputTurn);
			EnhancedInputComponent->BindAction(InputActioinJump, ETriggerEvent::Triggered, this, &ThisClass::InputJump);
			EnhancedInputComponent->BindAction(InputActioinAttack, ETriggerEvent::Triggered, this, &ThisClass::InputAttack);
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

void ADefaultPlayerController::InputJump(const FInputActionValue& InputValue)
{
	if (AIPlayer* DefaultPlayer = Cast<AIPlayer>(GetPawn()))
	{
		DefaultPlayer->Jump();
	}
}

void ADefaultPlayerController::InputAttack(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Black, TEXT("Attack"));
	if (AIPlayer* DefaultPlayer = Cast<AIPlayer>(GetPawn()))
	{
		if (DefaultPlayer->AttackAnimMontage)
			DefaultPlayer->PlayAnimMontage(DefaultPlayer->AttackAnimMontage, 1.0f, TEXT("Attack"));
	}
}
