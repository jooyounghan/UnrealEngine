#include "Item/InventorySubsystem.h"
#include "Item/BaseItem.h"

UInventorySubsystem::UInventorySubsystem()
	: Super()
{
}

void UInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	for (int idx = 0; idx < 5; ++idx)
	{
		TObjectPtr<UBaseItem> DebugItem = NewObject<UBaseItem>();
		DebugItem->SetOccupiedSlotsCount(FIntPoint(1, 1));
		DebugItem->SetRootPositionFromDestination(FIntPoint(0, idx));
		DebugItem->SetCount(idx + 1);
		Items.Add(DebugItem);
	}
}

void UInventorySubsystem::Deinitialize()
{
	Super::Deinitialize();
}
