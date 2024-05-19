// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

struct FInputActionValue;

UCLASS()
class PORTFOLIO_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADefaultPlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void InputMove(const struct FInputActionValue& InputValue);
	void InputTurn(const struct FInputActionValue& InputValue);
	void InputJump(const struct FInputActionValue& InputValue);
	void InputAttack(const struct FInputActionValue& InputValue);
};
