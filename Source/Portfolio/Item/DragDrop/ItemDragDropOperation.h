// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDragDropOperation.generated.h"

class UBaseItem;

UCLASS()
class PORTFOLIO_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	UItemDragDropOperation(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY()
	TObjectPtr<UBaseItem> Item;
};
