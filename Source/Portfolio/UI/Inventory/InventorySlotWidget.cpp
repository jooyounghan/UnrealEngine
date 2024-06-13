#include "UI/Inventory/InventorySlotWidget.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"

UInventorySlotWidget::UInventorySlotWidget(
	const FObjectInitializer& ObjectInitializer
)
	: Super(ObjectInitializer)
{
}

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SizeBox_Root->SetWidthOverride(50.f);
	SizeBox_Root->SetHeightOverride(50.f);
}

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Drag Button Down"));
		Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	return Reply;
}

FReply UInventorySlotWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Drag Button Up"));
		Reply.EndDragDrop();
	}
	return Reply;
}

void UInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	return;
}

void UInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

void UInventorySlotWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Drag Enter"));
}

void UInventorySlotWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Drag Leave"));
}

bool UInventorySlotWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool OnDragOver = Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Drag Over"));

	return OnDragOver;
}

bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool OnDrop = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Drop"));
	return OnDrop;
}

void UInventorySlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Black, TEXT("Drag Cancelled"));
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}
