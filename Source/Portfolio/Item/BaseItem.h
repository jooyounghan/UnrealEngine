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
	FIntPoint ItemPosition = FIntPoint(0, 0);

public:
	inline void SetOccupiedSlotsCount(const FIntPoint& OccupiedSlotsCountIn) { OccupiedSlotsCount = OccupiedSlotsCountIn; }
	inline void SetPosition(const FIntPoint& NewPosition) { ItemPosition = NewPosition; }
	inline const FIntPoint GetOccupiedSlotsCount() { return OccupiedSlotsCount; }
	inline const FIntPoint GetPosition() { return ItemPosition; }

protected:
	UPROPERTY()
	FIntPoint ItemSelectedOffset = FIntPoint(0, 0);

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
	void UpdateSelect(const FIntPoint& NewSelectedPosition);

public:
	TArray<FIntPoint> GetPositionsToDestination(
		const FIntPoint& DestinationPos
	);

};
