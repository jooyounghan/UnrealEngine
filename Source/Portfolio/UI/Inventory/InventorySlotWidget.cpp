#include "UI/Inventory/InventorySlotWidget.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"

FVector2D UInventorySlotWidget::SlotWidgetSize = FVector2D(50.0, 50.0);

UInventorySlotWidget::UInventorySlotWidget(
	const FObjectInitializer& ObjectInitializer
)
	: Super(ObjectInitializer)
{
}

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SizeBox_Root->SetWidthOverride(static_cast<float>(SlotWidgetSize.X));
	SizeBox_Root->SetHeightOverride(static_cast<float>(SlotWidgetSize.Y));
}

