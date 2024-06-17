// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemDragDropWidget.generated.h"

class USizeBox;
class UTextBlock;
class UImage;
class UBaseITem;

UCLASS()
class PORTFOLIO_API UItemDragDropWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UItemDragDropWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void Init(UBaseItem* ItemIn);

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SetAttachedToMouse();

public:
	UPROPERTY()
	TObjectPtr<UBaseItem> Item;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Count;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;
};
