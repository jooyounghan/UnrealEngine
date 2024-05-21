// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Asset/InputPrimaryDataAsset.h"
#include "Log/LogChannel.h"
#include "UObject/ObjectSaveContext.h"

void UInputPrimaryDataAsset::PreSave(FObjectPreSaveContext ObjectSaveContext)
{
    Super::PreSave(ObjectSaveContext);

    AssetLabelTagToSet.Empty();

    for (const auto& GroupTagToAssetSet : AssetGroupTagToSet)
    {
        const FGameplayTag& GroupTag = GroupTagToAssetSet.Key;
        const FAssetSet& AssetSet = GroupTagToAssetSet.Value;

        for (const FAssetEntry& Entry : AssetSet.AssetEntries)
        {
            AssetTagToPath.FindOrAdd(Entry.AssetTag, Entry.AssetPath);
            for (const FGameplayTag& LabelTag : Entry.AssetLabelTags)
            {
                AssetLabelTagToSet.FindOrAdd(LabelTag).AssetEntries.Emplace(Entry);
            }
        }
    }
}

void UInputPrimaryDataAsset::PostLoad()
{
    Super::PostLoad();
}

FSoftObjectPath UInputPrimaryDataAsset::GetAssetPathByAssetTag(const FGameplayTag& AssetTag)
{
    FSoftObjectPath* AssetPath = AssetTagToPath.Find(AssetTag);
    if (AssetPath == nullptr)
    {
        UE_LOG(LogAssetLoad, Fatal, TEXT("Can't Find the Asset Set [%s] by Asset Tag"), *AssetTag.ToString());
    }
    return *AssetPath;
}


FAssetSet UInputPrimaryDataAsset::GetAssetSetByLabelTag(const FGameplayTag& LabelTag)
{
    FAssetSet* AssetSet = AssetLabelTagToSet.Find(LabelTag);
    if (AssetSet == nullptr)
    {
        UE_LOG(LogAssetLoad, Fatal, TEXT("Can't Find the Asset Set [%s] by Label Tag"), *LabelTag.ToString());
    }
    return *AssetSet;
}
