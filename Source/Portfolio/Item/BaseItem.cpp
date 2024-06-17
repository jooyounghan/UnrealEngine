// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseItem.h"

UBaseItem::UBaseItem()
	: Super()
{
}

TArray<FIntPoint> UBaseItem::GetPositionsToDestination(
	const FIntPoint& DestinationPos
)
{
	TArray<FIntPoint> Positions;

	FIntPoint NewRootPosition = DestinationPos - SelectedSlotOffsetFromRoot;

	for (int Yidx = 0; Yidx < OccupiedSlotsCount.Y; ++Yidx)
	{
		for (int Xidx = 0; Xidx < OccupiedSlotsCount.X; ++Xidx)
		{
			Positions.Add(NewRootPosition + FIntPoint(Xidx, Yidx));
		}
	}

	return Positions;
}
