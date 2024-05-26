// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

struct FInputActionValue;
class UAnimMontage;
class UNiagaraSystem;
class ACreature;
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

protected:
	void TraceMouseHit();

protected:
	UPROPERTY(Category = Input, EditAnywhere, BlueprintReadOnly)
	float MoveMousePresssedTreshold = 0.3f;

	UPROPERTY(Category = Input, EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> FXCursor;

protected:
	FVector CachedDestination = FVector::ZeroVector;
	float MoveMousePressedTime = 0.f;

protected:
	UPROPERTY(Category = Input, BlueprintReadOnly)
	float ZoomSpeed = 20.f;

protected:
	UPROPERTY(Category = Target, BlueprintReadOnly)
	TObjectPtr<ACreature> TargetedCreature;

protected:
	UPROPERTY(Category = Target, BlueprintReadOnly)
	TObjectPtr<AUnitEnemy> CursorTargetingCreature;

	UPROPERTY(Category = Target, BlueprintReadOnly)
	TObjectPtr<AUnitEnemy> CtrlTargetingEnemy;

	UPROPERTY(Category = Target, BlueprintReadOnly)
	float EnemyDistance = 10000.f;

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
