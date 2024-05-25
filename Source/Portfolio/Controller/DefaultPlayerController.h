// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

struct FInputActionValue;
class UAnimMontage;
class UNiagaraSystem;

UCLASS()
class PORTFOLIO_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADefaultPlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsCtrlPressed = false;

protected:
	UPROPERTY(Category = Input, EditAnywhere, BlueprintReadOnly)
	float MoveMousePresssedTreshold = 0.3f;

	UPROPERTY(Category = Input, EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> FXCursor;

protected:
	FVector CachedDestination = FVector::ZeroVector;
	float MoveMousePressedTime = 0.f;

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
	void InputAddtiveCtrl(const struct FInputActionValue& InputValue);
};
