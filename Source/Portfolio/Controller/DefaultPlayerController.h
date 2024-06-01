// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

struct FInputActionValue;
class UAnimMontage;
class UNiagaraSystem;
class ACreature;
class AUnitPlayer;
class AUnitEnemy;

UCLASS()
class PORTFOLIO_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADefaultPlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

public:
	virtual void StopMovement();

protected:
	void ShowControllerTargeting();

protected:
	void TraceMouseHit();

protected:
	UCharacterStateSubsystem* StateSubsystem;

protected:
	UPROPERTY(Category = Input, EditAnywhere, BlueprintReadOnly)
	float MoveMousePresssedTreshold = 0.3f;

	UPROPERTY(Category = Input, EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> FXCursor;

protected:
	FVector CachedDestination = FVector::ZeroVector;
	float MoveMousePressedTime = 0.f;
	float ZoomSpeed = 20.f;

protected:
	UPROPERTY(Category = Character, BlueprintReadOnly)
	TObjectPtr<AUnitPlayer> PossesedCharacter;

protected:
	UPROPERTY(Category = Target, BlueprintReadOnly)
	TObjectPtr<ACreature> TargetedCreature;

protected:
	UPROPERTY(Category = Target, VisibleAnywhere)
	TObjectPtr<ACreature> CursorTargetingCreature;

	UPROPERTY(Category = Target, VisibleAnywhere)
	TObjectPtr<ACreature> CtrlTargetingEnemy;

private:
	void InputMoveByKey(const struct FInputActionValue& InputValue);
	void InputZoom(const struct FInputActionValue& InputValue);
	void InputTurn(const struct FInputActionValue& InputValue);
	void InputAttack(const struct FInputActionValue& InputValue);

private:
	void OnMouseMoveStarted();
	void OnMouseMoveTriggered();
	void OnMouseMoveReleased();

private:
	void OnCtrlTargetingStarted();
	void OnCtrlTargetingTriggered();
	void OnCtrlTargetingReleased();
};
