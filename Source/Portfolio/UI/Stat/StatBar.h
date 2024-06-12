// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatBar.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UStatBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UStatBar(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;

public:
	void SetRatio(float Percent);

public:
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	TObjectPtr<class UProgressBar> StatProgressBar;
};
