// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GamePlayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputDataAsset.generated.h"

class UInputMappingContext;
class UInputAction;

USTRUCT()
struct FInputActionSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FGameplayTag InputSpecificTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InputAction = nullptr;
};

UCLASS()
class PORTFOLIO_API UInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UInputAction* FindInputActionByTag(const FGameplayTag& SpecificTag) const;

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere)
	TArray<FInputActionSet> InputActions;
};
