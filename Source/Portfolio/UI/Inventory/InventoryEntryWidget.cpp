// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryEntryWidget.h"

#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "UI/Inventory/InventorySlotWidget.h"
#include "Item/BaseItem.h"

#include "Item/DragDrop/ItemDragDropOperation.h"
#include "Item/DragDrop/ItemDragDropWidget.h"

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

	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Mouse Enter"));
	Image_IconHover->SetOpacity(1.f);
}

void UInventoryEntryWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Mouse Leave"));
	Image_IconHover->SetOpacity(0.f);
}

FReply UInventoryEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}
	
	FVector2D ItemWidgetPos = RootSlotWidget->GetCachedGeometry().AbsoluteToLocal(InGeometry.LocalToAbsolute(UInventorySlotWidget::SlotWidgetSize));
	FIntPoint ItemSlotPos = FIntPoint(ItemWidgetPos.X / UInventorySlotWidget::SlotWidgetSize.X / ItemWidgetPos.Y / UInventorySlotWidget::SlotWidgetSize.Y);
	Item->UpdateSelect(ItemSlotPos);

	return Reply;
}

FReply UInventoryEntryWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Drag Button Up"));
		Reply.EndDragDrop();
	}
	return Reply;
}

void UInventoryEntryWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UItemDragDropOperation* DragDrop = NewObject<UItemDragDropOperation>();

	UItemDragDropWidget* DragDropWidget = CreateWidget<UItemDragDropWidget>(GetOwningPlayer(), DragDropWidgetClass);
	DragDropWidget->Init(Item->GetOccupiedSlotsCount(), Item->GetIcon(), Item->GetCount());

	DragDrop->DefaultDragVisual = DragDropWidget;
	DragDrop->Pivot = EDragPivot::MouseDown;
	DragDrop->Item = Item;

	OutOperation = DragDrop;
}

void UInventoryEntryWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Drag Enter"));
}

void UInventoryEntryWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Drag Leave"));
}

bool UInventoryEntryWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool OnDragOver = Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Drag Over"));

	return OnDragOver;
}

bool UInventoryEntryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool OnDrop = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Drop"));
	return OnDrop;
}

void UInventoryEntryWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Drag Cancelled"));
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}