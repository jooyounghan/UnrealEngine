#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotsWidget.generated.h"

class UUniformGridPanel;
class UCanvasPanel;
class UInventorySlotWidget;
class UInventoryEntryWidget;
class UBaseItem;

UCLASS()
class PORTFOLIO_API UInventorySlotsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInventorySlotsWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void NativeConstruct() override;

public:
	void UpdateInventoryEntries(
		const FIntPoint& DestinationPoint, 
		UBaseItem* Item
	);

public:
	void RemoveItemFromSlots(UBaseItem* Item);

protected:
	bool CheckIsPlaceable(
		const FIntPoint& DestinationPoint,
		UBaseItem* ChekcingItem,
		UBaseItem*& PreOccupiedItemOut
	);

protected:
	// TODO : Inventory SubSystem에서 Inventory와 관련된 모든 데이터를 처리하도록 변경
	UPROPERTY()
	int32 XSlotNum = 10;
	UPROPERTY()
	int32 YSlotNum = 14;

protected:
	UPROPERTY()
	TSubclassOf<UInventorySlotWidget> InventorySlotClass;
	UPROPERTY()
	TArray<TObjectPtr<UInventorySlotWidget>> InventorySlots;

protected:
	UPROPERTY()
	TSubclassOf<UInventoryEntryWidget> InventoryEntryClass;
	UPROPERTY()
	TArray<TObjectPtr<UInventoryEntryWidget>> InventoryEntries;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> UniformGridPanel_Slots;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel_Entries;

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
