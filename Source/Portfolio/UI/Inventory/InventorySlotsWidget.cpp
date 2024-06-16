#include "UI/Inventory/InventorySlotsWidget.h"
#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/InventoryEntryWidget.h"

#include "Components/UniformGridPanel.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#include "Item/BaseItem.h"
#include "Item/InventorySubsystem.h"

#include "Subsystems/SubsystemBlueprintLibrary.h"

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

	ConstructorHelpers::FClassFinder<UInventoryEntryWidget> FindEntryWidgetClass(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Inventory/WBP_InventoryEntry.WBP_InventoryEntry_C'")
	);
	if (FindEntryWidgetClass.Succeeded())
	{
		InventoryEntryClass = FindEntryWidgetClass.Class;
	}
}


void UInventorySlotsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventorySlots.SetNum(XSlotNum * YSlotNum);
	InventoryEntries.SetNum(XSlotNum * YSlotNum);

	// Initialize Default Slots
	for (int32 y = 0; y < YSlotNum; ++y)
	{
		for (int32 x = 0; x < XSlotNum; ++x)
		{
			const int32 index = y * XSlotNum + x;
			TObjectPtr<UInventorySlotWidget>& InventoryWidget = InventorySlots[index];
			InventoryWidget = CreateWidget<UInventorySlotWidget>(GetOwningPlayer(), InventorySlotClass);
			UniformGridPanel_Slots->AddChildToUniformGrid(InventoryWidget, y, x);
		}
	}

	UInventorySubsystem* Inventory = Cast<UInventorySubsystem>(
		USubsystemBlueprintLibrary::GetLocalPlayerSubsystem(
			this, UInventorySubsystem::StaticClass()
		)
	);

	// Initialize Item Setting
	if (Inventory)
	{
		const TArray<TObjectPtr<UBaseItem>>& Items = Inventory->GetItems();
		for (const TObjectPtr<UBaseItem>& Item : Items)
		{
			UpdateInventoryEntries(Item->GetPosition(), Item);
		}
	}
}

void UInventorySlotsWidget::UpdateInventoryEntries(
	const FIntPoint& DestinationPoint, 
	UBaseItem* Item
)
{
	UBaseItem* PreOccupiedItem = nullptr;
	bool bIsPlaceable = CheckIsPlaceable(DestinationPoint, Item, PreOccupiedItem);

	TArray<FIntPoint> Positions = Item->GetPositionsToDestination(DestinationPoint);

	if (PreOccupiedItem)
	{
		// Remove Entries Of PreOccupiedItem
	}

	for (const FIntPoint& Position : Positions)
	{
		int32 EntryIndex = Position.X + Position.Y * XSlotNum;
		UInventoryEntryWidget* EntryWidget = CreateWidget<UInventoryEntryWidget>(GetOwningPlayer(), InventoryEntryClass);
		InventoryEntries[EntryIndex] = EntryWidget;

		EntryWidget->Init(InventorySlots[EntryIndex], Item);

		const FVector2D SlotWidgetSize = UInventorySlotWidget::SlotWidgetSize;

		UCanvasPanelSlot* CanvasPanelSlot = CanvasPanel_Entries->AddChildToCanvas(EntryWidget);
		CanvasPanelSlot->SetAutoSize(true);
		CanvasPanelSlot->SetPosition(FVector2D(Position.X * SlotWidgetSize.X, Position.Y * SlotWidgetSize.Y));

	}
}

bool UInventorySlotsWidget::CheckIsPlaceable(
	const FIntPoint& DestinationPoint, 
	UBaseItem* ChekcingItem, 
	UBaseItem*& PreOccupiedItemOut
)
{
	TArray<FIntPoint> CheckPositions = ChekcingItem->GetPositionsToDestination(DestinationPoint);

	PreOccupiedItemOut = nullptr;
	bool bIsPlaceable = true;

	// First check for knowing this action is accessable
	for (const FIntPoint& CheckPosition : CheckPositions)
	{
		int32 CheckIndex = CheckPosition.X + CheckPosition.Y * XSlotNum;

		if (UInventoryEntryWidget* EntryWidget = InventoryEntries[CheckIndex])
		{
			UBaseItem* EntryWidgetItem = EntryWidget->Item;
			if (PreOccupiedItemOut != nullptr)
			{
				// If two or more Items are located in the checking position,
				// Placing item can't happened.
				bIsPlaceable = false;
				break;
			}
			else
			{
				PreOccupiedItemOut = EntryWidgetItem == ChekcingItem ? nullptr : EntryWidgetItem;
			}
		}
		else
		{

		}
	}

	return bIsPlaceable;
}