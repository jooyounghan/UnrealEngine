// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseItem.h"

UBaseItem::UBaseItem()
	: Super()
{
}

inline void UBaseItem::UpdateSelect(const FIntPoint& NewSelectedPosition) 
{ 
	ItemSelectedOffset = NewSelectedPosition - ItemPosition; 
}

TArray<FIntPoint> UBaseItem::GetPositionsToDestination(
	const FIntPoint& DestinationPos
)
{
	TArray<FIntPoint> Positions;

	FIntPoint NewPosition = DestinationPos - ItemSelectedOffset;
	SetPosition(NewPosition);

	for (int Yidx = 0; Yidx < OccupiedSlotsCount.Y; ++Yidx)
	{
		for (int Xidx = 0; Xidx < OccupiedSlotsCount.X; ++Xidx)
		{
			Positions.Add(ItemPosition + FIntPoint(Xidx, Yidx));
		}
	}

	return Positions;
}
