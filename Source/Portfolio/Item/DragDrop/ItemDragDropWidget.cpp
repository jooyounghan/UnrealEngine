#include "Item/DragDrop/ItemDragDropWidget.h"

#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "UI/Inventory/InventorySlotWidget.h"

UItemDragDropWidget::UItemDragDropWidget(
	const FObjectInitializer& ObjectInitializer
)
	: Super(ObjectInitializer)
{
}

void UItemDragDropWidget::Init(
	const FIntPoint& OccupiedSlotsCountIn,
	UTexture2D* ItemIcon, int32 ItemCount
)
{
	const FVector2D& SlotWidgetSize = UInventorySlotWidget::SlotWidgetSize;
	SizeBox_Root->SetWidthOverride(SlotWidgetSize.X * OccupiedSlotsCountIn.X);
	SizeBox_Root->SetHeightOverride(SlotWidgetSize.Y * OccupiedSlotsCountIn.Y);

	Image_Icon->SetBrushFromTexture(ItemIcon);
	Text_Count->SetText((ItemCount > 1) ? FText::AsNumber(ItemCount) : FText::GetEmpty());
}

