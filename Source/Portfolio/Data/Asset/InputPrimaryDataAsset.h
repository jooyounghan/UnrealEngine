// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputPrimaryDataAsset.generated.h"

USTRUCT()
struct FAssetEntry
{
	GENERATED_BODY()

public:	 
	UPROPERTY(EditAnywhere)
	FGameplayTag AssetTag;

	UPROPERTY(EditAnywhere)
	FSoftObjectPath AssetPath;
	
	UPROPERTY(EditAnywhere)
	TArray<FGameplayTag> AssetLabelTags;
};

USTRUCT()
struct FAssetSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FAssetEntry> AssetEntries;
};

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UInputPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;
	virtual void PostLoad() override;

private:
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, FAssetSet> AssetGroupTagToSet;

private:
	UPROPERTY()
	TMap<FGameplayTag, FSoftObjectPath> AssetTagToPath;

	UPROPERTY()
	TMap<FGameplayTag, FAssetSet> AssetLabelTagToSet;

public:
	FSoftObjectPath GetAssetPathByAssetTag(const FGameplayTag& AssetTag);
	FAssetSet GetAssetSetByLabelTag(const FGameplayTag& LabelTag);
};
