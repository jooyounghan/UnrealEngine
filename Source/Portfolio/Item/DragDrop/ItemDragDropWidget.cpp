#include "Item/DragDrop/ItemDragDropWidget.h"
#include "Item/BaseItem.h"

#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "UI/Inventory/InventorySlotWidget.h"
#include "Kismet/GameplayStatics.h"

UItemDragDropWidget::UItemDragDropWidget(
	const FObjectInitializer& ObjectInitializer
)
	: Super(ObjectInitializer)
{
}

void UItemDragDropWidget::Init(UBaseItem* ItemIn)
{
	if (ItemIn)
	{
		Item = ItemIn;

		const FIntPoint& OccupiedSlotsCount = Item->GetOccupiedSlotsCount();
		const FVector2D& SlotWidgetSize = UInventorySlotWidget::SlotWidgetSize;
		SizeBox_Root->SetWidthOverride(SlotWidgetSize.X * OccupiedSlotsCount.X);
		SizeBox_Root->SetHeightOverride(SlotWidgetSize.Y * OccupiedSlotsCount.Y);

		Image_Icon->SetBrushFromTexture(Item->GetIcon());

		const int32& ItemCount = Item->GetCount();
		Text_Count->SetText((ItemCount > 1) ? FText::AsNumber(ItemCount) : FText::GetEmpty());
	}
}

void UItemDragDropWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UItemDragDropWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	SetAttachedToMouse();
}

void UItemDragDropWidget::SetAttachedToMouse()
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FVector2D MousePosition;
		if (PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y))
		{
			SetPositionInViewport(MousePosition);
		}
	}
}

