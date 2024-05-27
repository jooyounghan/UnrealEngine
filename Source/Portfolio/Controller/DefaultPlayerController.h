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

protected:
	virtual void StopMovement();

protected:
	void TraceMouseHit();
	void ShowTargeted();
	void ChaseAndAttackTarget();

protected:
	void SetTargetToAttack(ACreature* Target);
	void ResetTargetToAttack();
	inline void SpendAttackable() { bIsAttackable = false; }

protected:
	bool IsNearForAttacking(const double& Distance);
	bool bIsAttackable = false;

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

	UPROPERTY(Category = Target, BlueprintReadOnly)
	TObjectPtr<ACreature> TargetToAttack;

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
