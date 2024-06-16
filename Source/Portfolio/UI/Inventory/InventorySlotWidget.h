// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

class USizeBox;
class UImage;

UCLASS()
class PORTFOLIO_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInventorySlotWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void NativeConstruct() override;

public:
	static FVector2D SlotWidgetSize;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Slot;
};
