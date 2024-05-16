// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "GameplayTagContainer.h"

#include "Log/LogChannel.h"
#include "Data/Asset/InputPrimaryDataAsset.h"

#include "DefaultAssetManager.generated.h"

DECLARE_DELEGATE_TwoParams(FAsyncLoadCompleteDelegate, const FGameplayTag&, UObject*);

UCLASS()
class PORTFOLIO_API UDefaultAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	UDefaultAssetManager();
	
public:
	static UDefaultAssetManager& Get();	
	static void Initialize();

public:
	template<typename AssetType>
	static AssetType* GetAssetByAssetTag(const FGameplayTag& AssetTag);

public:
	static void LoadSyncByLabel(const FGameplayTag& LabelTag);
	static void LoadSyncByPath(const FGameplayTag& AssetTag, const FSoftObjectPath& AssetPath);

public:
	static void LoadAsyncByLabel(const FGameplayTag& LabelTag, FAsyncLoadCompleteDelegate CompletedDelegate = FAsyncLoadCompleteDelegate());
	static void LoadAsyncByPath(const FGameplayTag& AssetTag, const FSoftObjectPath& AssetPath, FAsyncLoadCompleteDelegate CompletedDelegate = FAsyncLoadCompleteDelegate());

private:
	void LoadPreloadAssets();
	void AddLoadedAssetByAssetTag(const FGameplayTag& AssetTag, const UObject* Asset);

protected:
	UPROPERTY()
	TObjectPtr<UInputPrimaryDataAsset> LoadedInputPrimaryDataAssets;

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<const UObject>> AssetTagToLoadedAsset;
};

template<typename AssetType>
AssetType* UDefaultAssetManager::GetAssetByAssetTag(const FGameplayTag& AssetTag)
{
	UInputPrimaryDataAsset* AssetData = Get().LoadedInputPrimaryDataAssets;
	check(AssetData);

	AssetType* LoadedAsset = nullptr;
	const FSoftObjectPath& AssetPath = AssetData->GetAssetPathByAssetTag(AssetTag);
	if (AssetPath.IsValid())
	{
		LoadedAsset = Cast<AssetType>(AssetPath.ResolveObject());
		if (LoadedAsset == nullptr)
		{
			UE_LOG(LogAssetLoad, Warning, TEXT("Attempted sync loading because asset hadn't loaded yet [%s]."), *AssetPath.ToString());
			LoadedAsset = Cast<AssetType>(AssetPath.TryLoad());
		}
	}
	return LoadedAsset;
}
