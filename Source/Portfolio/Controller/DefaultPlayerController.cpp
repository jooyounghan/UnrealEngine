// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DefaultPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "Data/DefaultAssetManager.h"
#include "Data/Asset/InputDataAsset.h"
#include "Util/DefaultGamePlayTags.h"

#include "Character/IPlayer.h"

ADefaultPlayerController::ADefaultPlayerController(const FObjectInitializer& ObjectInitializer)
	: APlayerController(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::GrabHand;
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
			auto InputActionMoveByKey = InputData->FindInputActionByTag(GamePlayTags::InputActionMoveByKey);
			auto InputActionMoveByMouse = InputData->FindInputActionByTag(GamePlayTags::InputActionMoveByMouse);
			auto InputActionTurn = InputData->FindInputActionByTag(GamePlayTags::InputActionTurn);
			auto InputActioAttack = InputData->FindInputActionByTag(GamePlayTags::InputActionAttack);

			auto InputAdditiveCtrl = InputData->FindInputActionByTag(GamePlayTags::InputAdditiveCtrl);

			EnhancedInputComponent->BindAction(InputActionMoveByKey, ETriggerEvent::Triggered, this, &ThisClass::InputMoveByKey);
			EnhancedInputComponent->BindAction(InputActionTurn, ETriggerEvent::Triggered, this, &ThisClass::InputTurn);
			EnhancedInputComponent->BindAction(InputActioAttack, ETriggerEvent::Triggered, this, &ThisClass::InputAttack);

			EnhancedInputComponent->BindAction(InputActionMoveByMouse, ETriggerEvent::Started, this, &ThisClass::OnMouseMoveStarted);
			EnhancedInputComponent->BindAction(InputActionMoveByMouse, ETriggerEvent::Triggered, this, &ThisClass::OnMouseMoveTriggered);
			EnhancedInputComponent->BindAction(InputActionMoveByMouse, ETriggerEvent::Completed, this, &ThisClass::OnMouseMoveReleased);
			EnhancedInputComponent->BindAction(InputActionMoveByMouse, ETriggerEvent::Canceled, this, &ThisClass::OnMouseMoveReleased);

			EnhancedInputComponent->BindAction(InputAdditiveCtrl, ETriggerEvent::Started, this, &ThisClass::InputAddtiveCtrl);
			EnhancedInputComponent->BindAction(InputAdditiveCtrl, ETriggerEvent::Completed, this, &ThisClass::InputAddtiveCtrl);
		}
	}
}

void ADefaultPlayerController::InputMoveByKey(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();
	MovementVector.Normalize();

	FRotator Rotator = GetControlRotation();
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0, Rotator.Yaw, 0));
	FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));

	GetPawn()->AddMovementInput(ForwardVector, MovementVector.X);
	GetPawn()->AddMovementInput(RightVector, MovementVector.Y);
}

void ADefaultPlayerController::InputZoom(const FInputActionValue& InputValue)
{

}

void ADefaultPlayerController::InputTurn(const FInputActionValue& InputValue)
{
	if (bIsCtrlPressed)
	{
		FVector2D AngleVector = InputValue.Get<FVector2D>();
		AddYawInput(AngleVector.X);
		AddPitchInput(AngleVector.Y);
	}

}

void ADefaultPlayerController::InputAttack(const FInputActionValue& InputValue)
{
	if (AIPlayer* DefaultPlayer = Cast<AIPlayer>(GetPawn()))
	{
		if (DefaultPlayer->AttackAnimMontage)
		{
			const FString AttackFormatter = FString(TEXT("Attack_{0}"));
			const FString AttackFormatted = FString::Format(*AttackFormatter, { rand() % DefaultPlayer->AttackAnimMontage->GetNumSections() });
			DefaultPlayer->PlayAnimMontage(DefaultPlayer->AttackAnimMontage, 1.0f, *AttackFormatted);
		}
	}
}

void ADefaultPlayerController::OnMouseMoveStarted()
{
	StopMovement();
}

void ADefaultPlayerController::OnMouseMoveTriggered()
{
	MoveMousePressedTime += GetWorld()->GetDeltaSeconds();

	FHitResult Hit;
	bool bHitSuccess = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bHitSuccess)
	{
		CachedDestination = Hit.Location;
	}

	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection);
	}
}

void ADefaultPlayerController::OnMouseMoveReleased()
{
	if (MoveMousePressedTime < MoveMousePresssedTreshold)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination);
	}
	MoveMousePressedTime = 0.f;
}

void ADefaultPlayerController::InputAddtiveCtrl(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(0, 0.5f, FColor::Cyan, TEXT("CTRL"));
	
	const bool bCurrentCtrlPressed = bIsCtrlPressed;
	bIsCtrlPressed = !bCurrentCtrlPressed;
	bShowMouseCursor = bCurrentCtrlPressed;
}
