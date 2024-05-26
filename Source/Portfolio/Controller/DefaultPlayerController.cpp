// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DefaultPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "Data/DefaultAssetManager.h"
#include "Data/Asset/InputDataAsset.h"
#include "Util/DefaultGamePlayTags.h"

#include "Character/UnitPlayer.h"
#include "Character/UnitEnemy.h"

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
			auto InputActionZoom = InputData->FindInputActionByTag(GamePlayTags::InputActionZoom);
			auto InputActionAttack = InputData->FindInputActionByTag(GamePlayTags::InputActionAttack);

			auto InputAdditiveCtrl = InputData->FindInputActionByTag(GamePlayTags::InputAdditiveCtrl);

			EnhancedInputComponent->BindAction(InputActionMoveByKey, ETriggerEvent::Triggered, this, &ThisClass::InputMoveByKey);
			EnhancedInputComponent->BindAction(InputActionTurn, ETriggerEvent::Triggered, this, &ThisClass::InputTurn);
			EnhancedInputComponent->BindAction(InputActionAttack, ETriggerEvent::Triggered, this, &ThisClass::InputAttack);
			EnhancedInputComponent->BindAction(InputActionZoom, ETriggerEvent::Triggered, this, &ThisClass::InputZoom);


			EnhancedInputComponent->BindAction(InputActionMoveByMouse, ETriggerEvent::Started, this, &ThisClass::OnMouseMoveStarted);
			EnhancedInputComponent->BindAction(InputActionMoveByMouse, ETriggerEvent::Triggered, this, &ThisClass::OnMouseMoveTriggered);
			EnhancedInputComponent->BindAction(InputActionMoveByMouse, ETriggerEvent::Completed, this, &ThisClass::OnMouseMoveReleased);
			EnhancedInputComponent->BindAction(InputActionMoveByMouse, ETriggerEvent::Canceled, this, &ThisClass::OnMouseMoveReleased);

			EnhancedInputComponent->BindAction(InputAdditiveCtrl, ETriggerEvent::Started, this, &ThisClass::OnCtrlTargetingStarted);
			EnhancedInputComponent->BindAction(InputAdditiveCtrl, ETriggerEvent::Triggered, this, &ThisClass::OnCtrlTargetingTriggered);
			EnhancedInputComponent->BindAction(InputAdditiveCtrl, ETriggerEvent::Completed, this, &ThisClass::OnCtrlTargetingReleased);
			EnhancedInputComponent->BindAction(InputAdditiveCtrl, ETriggerEvent::Canceled, this, &ThisClass::OnCtrlTargetingReleased);
		}
	}
}

void ADefaultPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	TraceMouseHit();
}

void ADefaultPlayerController::TraceMouseHit()
{	
	FHitResult HitResultOut;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, HitResultOut);

	AUnitEnemy* Creature = Cast<AUnitEnemy>(HitResultOut.GetActor());
	if (Creature)
	{
		if (CursorTargetingCreature != Creature)
		{
			if (CursorTargetingCreature)
				CursorTargetingCreature->UnTarget();

			Creature->Target();
			CursorTargetingCreature = Creature;

			DrawDebugSphere(GetWorld(), CursorTargetingCreature->GetActorLocation(), 100.f, 10, FColor::Red);
		}
		else
		{
			DrawDebugSphere(GetWorld(), CursorTargetingCreature->GetActorLocation(), 100.f, 10, FColor::Red);
		}
	}
}

void ADefaultPlayerController::InputMoveByKey(const FInputActionValue& InputValue)
{
	StopMovement();
	FVector2D MovementVector = InputValue.Get<FVector2D>();
	MovementVector.Normalize();
	AUnitPlayer* UnitPlayer = Cast<AUnitPlayer>(GetPawn());
	
	if (UnitPlayer)
	{
		FRotator Rotator = UnitPlayer->CameraComponent->GetComponentRotation();
		FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0, Rotator.Yaw, 0));
		FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));

		UnitPlayer->AddMovementInput(ForwardVector, MovementVector.X);
		UnitPlayer->AddMovementInput(RightVector, MovementVector.Y);
	}
}

void ADefaultPlayerController::InputZoom(const FInputActionValue& InputValue)
{
	if (AUnitPlayer* DefaultPlayer = Cast<AUnitPlayer>(GetPawn()))
	{
		float ZoomValue = InputValue.Get<float>() * ZoomSpeed;
		const float& CurrentSpringArmLength = DefaultPlayer->GetSpringArmLength();
		DefaultPlayer->SetSringArmLength(CurrentSpringArmLength - ZoomValue);
	}
}

void ADefaultPlayerController::InputTurn(const FInputActionValue& InputValue)
{
	FVector2D AngleVector = InputValue.Get<FVector2D>();
	AddYawInput(AngleVector.X);
	AddPitchInput(-AngleVector.Y);
}

void ADefaultPlayerController::InputAttack(const FInputActionValue& InputValue)
{





	if (AUnitPlayer* DefaultPlayer = Cast<AUnitPlayer>(GetPawn()))
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
	bool bHitSuccess = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);

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

void ADefaultPlayerController::OnCtrlTargetingStarted()
{
	FHitResult HitResultOut;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResultOut);

	AActor* Floor = HitResultOut.GetActor();
	if (Floor)
	{
		TArray<AActor*> FoundEnemys;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnitEnemy::StaticClass(), FoundEnemys);

		float LocalEnemyDistance = EnemyDistance;

		for (AActor* Enemy : FoundEnemys)
		{
			const double Distance = (Enemy->GetActorLocation() - HitResultOut.Location).Length();
			if (LocalEnemyDistance > Distance)
			{
				LocalEnemyDistance = Distance;
				CtrlTargetingEnemy = Cast<AUnitEnemy>(Enemy);
			}
		}
	}
}

void ADefaultPlayerController::OnCtrlTargetingTriggered()
{
	FVector WorldLocation, WorldDirection;
	if (!DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
		return;

	FVector CameraLocation;
	FRotator CameraRotation;
	GetPlayerViewPoint(CameraLocation, CameraRotation);

	float DesiredDistance = 1000.0f; // 필요에 따라 조정
	FVector TargetLocation = CameraLocation + WorldDirection * DesiredDistance;

	if (CtrlTargetingEnemy)
	{
		DrawDebugLine(
			GetWorld(),
			CtrlTargetingEnemy->GetActorLocation(),
			TargetLocation,
			FColor::Blue,
			false, -1.F,
			0xFF
		);
	}
}

void ADefaultPlayerController::OnCtrlTargetingReleased()
{
	CtrlTargetingEnemy = nullptr;
}