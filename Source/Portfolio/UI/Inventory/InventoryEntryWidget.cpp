// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryEntryWidget.h"
#include "UI/Inventory/InventorySlotWidget.h"

#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "Item/BaseItem.h"
#include "Item/InventorySubsystem.h"
#include "Item/DragDrop/ItemDragDropWidget.h"

#include "Subsystems/SubsystemBlueprintLibrary.h"

UInventoryEntryWidget::UInventoryEntryWidget(
	const FObjectInitializer& ObjectInitializer
)
	: Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UItemDragDropWidget> FindDragDropWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Inventory/WBP_ItemDragDrop.WBP_ItemDragDrop_C'"));
	if (FindDragDropWidgetClass.Succeeded())
	{
		DragDropWidgetClass = FindDragDropWidgetClass.Class;
	}
}

void UInventoryEntryWidget::Init(UInventorySlotWidget* RootSlotWidgetIn, UBaseItem* ItemIn)
{
	RootSlotWidget = RootSlotWidgetIn;
	Item = ItemIn;

	const int32& ItemCount = Item->GetCount();
	Text_Count->SetText((ItemCount > 1) ? FText::AsNumber(ItemCount) : FText::GetEmpty());
}

void UInventoryEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const FVector2D& SlotWidgetSize = UInventorySlotWidget::SlotWidgetSize;

	SizeBox_Root->SetWidthOverride(static_cast<float>(SlotWidgetSize.X));
	SizeBox_Root->SetHeightOverride(static_cast<float>(SlotWidgetSize.Y));
}


void UInventoryEntryWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	Image_IconHover->SetOpacity(1.f);
}

void UInventoryEntryWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	Image_IconHover->SetOpacity(0.f);
}

FReply UInventoryEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		UInventorySubsystem* Inventory = Cast<UInventorySubsystem>(
			USubsystemBlueprintLibrary::GetLocalPlayerSubsystem(
				this, UInventorySubsystem::StaticClass()
			)
		);

		if (Inventory)
		{
			// Picking Item
			if (Inventory->SelectedItem == nullptr)
			{
				FVector2D OffsetPositionFromRoot = RootSlotWidget->GetCachedGeometry().AbsoluteToLocal(InGeometry.LocalToAbsolute(UInventorySlotWidget::SlotWidgetSize));
				FIntPoint OffsetSlotsFromRoot = FIntPoint(OffsetPositionFromRoot.X / UInventorySlotWidget::SlotWidgetSize.X / OffsetPositionFromRoot.Y / UInventorySlotWidget::SlotWidgetSize.Y);

				Item->UpdateSlotOffsetFromRoot(OffsetSlotsFromRoot);

				UItemDragDropWidget* SelectedItem = CreateWidget<UItemDragDropWidget>(GetOwningPlayer(), DragDropWidgetClass);

				SelectedItem->Init(Item);
				SelectedItem->AddToViewport();
				SelectedItem->SetAttachedToMouse();

				Inventory->SelectedItem = SelectedItem;
				Reply = FReply::Handled();
			}
			// Placing Item
			else
			{
				Reply = FReply::Unhandled();
			}

		}
	}

	return Reply;
}