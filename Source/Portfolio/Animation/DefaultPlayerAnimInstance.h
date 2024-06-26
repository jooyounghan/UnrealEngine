// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/StateInterface.h"
#include "Animation/AnimInstance.h"
#include "DefaultPlayerAnimInstance.generated.h"

class ACreature;
class UCharacterMovementComponent;

UCLASS()
class PORTFOLIO_API UDefaultPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UDefaultPlayerAnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	TObjectPtr<ACreature> Creature;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCharacterMovementComponent> CharacterMovement;

protected:
	UPROPERTY(BlueprintReadOnly)
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly)
	bool bShouldMove = false;

protected:
	UPROPERTY(BlueprintReadOnly)
	ECreatureState CharacterState;
};
