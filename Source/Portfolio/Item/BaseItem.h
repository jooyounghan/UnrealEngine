// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseItem.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UBaseItem : public UObject
{
	GENERATED_BODY()

public:
	UBaseItem();

protected:
	UPROPERTY()
	FIntPoint OccupiedSlotsCount = FIntPoint(0, 0);

	UPROPERTY()
	FIntPoint ItemRootPosition = FIntPoint(0, 0);

public:
	inline void SetOccupiedSlotsCount(const FIntPoint& OccupiedSlotsCountIn) { OccupiedSlotsCount = OccupiedSlotsCountIn; }
	inline void SetRootPositionFromDestination(const FIntPoint& DestinationPosition) { ItemRootPosition = DestinationPosition - SelectedSlotOffsetFromRoot; }
	inline const FIntPoint& GetOccupiedSlotsCount() { return OccupiedSlotsCount; }
	inline const FIntPoint& GetRootPosition() { return ItemRootPosition; }

protected:
	UPROPERTY()
	FIntPoint SelectedSlotOffsetFromRoot = FIntPoint(0, 0);

protected:
	int32 ItemCount = 0;

public:
	inline void SetCount(const int32& ItemCountIn) { ItemCount = ItemCountIn; }
	inline const int32& GetCount() { return ItemCount; }

protected:
	UPROPERTY()
	TObjectPtr<UTexture2D> Icon;

public:
	inline UTexture2D* GetIcon() { return Icon; }


public:
	inline void UpdateSlotOffsetFromRoot(const FIntPoint& SlotOffsetFromRootIn) { SelectedSlotOffsetFromRoot = SlotOffsetFromRootIn;}

public:
	TArray<FIntPoint> GetPositionsToDestination(
		const FIntPoint& DestinationPos
	);
	inline TArray<FIntPoint> GetPositions() { return GetPositionsToDestination(ItemRootPosition); }
};
