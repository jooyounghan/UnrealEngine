// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "InventorySubsystem.generated.h"

class UBaseItem;

UCLASS()
class PORTFOLIO_API UInventorySubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	UInventorySubsystem();

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	UPROPERTY()
	TArray<TObjectPtr<UBaseItem>> Items;

public:
	inline const TArray<TObjectPtr<UBaseItem>>& GetItems() { return Items; }

public:
	UPROPERTY()
	TObjectPtr<UItemDragDropWidget> SelectedItem;

};
