#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotsWidget.generated.h"

class UUniformGridPanel;
class UInventorySlotWidget;

UCLASS()
class PORTFOLIO_API UInventorySlotsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInventorySlotsWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	int32 XSlotNum = 10;
	UPROPERTY()
	int32 YSlotNum = 14;

protected:
	UPROPERTY()
	TSubclassOf<UInventorySlotWidget> InventorySlotClass;

	UPROPERTY()
	TArray<TObjectPtr<UInventorySlotWidget>> InventorySlots;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> UniformGridPanel_Slots;
};
