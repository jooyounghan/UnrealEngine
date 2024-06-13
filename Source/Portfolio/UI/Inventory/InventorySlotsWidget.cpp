#include "UI/Inventory/InventorySlotsWidget.h"
#include "UI/Inventory/InventorySlotWidget.h"
#include "Components/UniformGridPanel.h"

UInventorySlotsWidget::UInventorySlotsWidget(
	const FObjectInitializer& ObjectInitializer
)
	: Super(ObjectInitializer)

{
	ConstructorHelpers::FClassFinder<UInventorySlotWidget> FindSlotWidgetClass(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Inventory/WBP_InventorySlot.WBP_InventorySlot_C'")
	);

	if (FindSlotWidgetClass.Succeeded())
	{
		InventorySlotClass = FindSlotWidgetClass.Class;
	}
}

void UInventorySlotsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventorySlots.SetNum(XSlotNum * YSlotNum);

	for (int32 y = 0; y < YSlotNum; ++y)
	{
		for (int32 x = 0; x < XSlotNum; ++x)
		{
			const size_t index = static_cast<size_t>(y * XSlotNum + x);
			TObjectPtr<UInventorySlotWidget>& InventoryWidget = InventorySlots[index];
			InventoryWidget = CreateWidget<UInventorySlotWidget>(GetOwningPlayer(), InventorySlotClass);
			UniformGridPanel_Slots->AddChildToUniformGrid(InventoryWidget, y, x);
		}
	}
}
