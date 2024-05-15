// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAssetManager.h"
#include "DefaultGamePlayTags.h"

UDefaultAssetManager::UDefaultAssetManager()
	: Super()
{
}

UDefaultAssetManager& UDefaultAssetManager::Get()
{
	if (UDefaultAssetManager* AssetManager = Cast<UDefaultAssetManager>(GEngine->AssetManager))
	{
		return *AssetManager;
	}
	UE_LOG(LogAssetLoad, Fatal, TEXT("Can't Find UDefaultAssetManager"))
	return *NewObject<UDefaultAssetManager>();
}

void UDefaultAssetManager::Initialize()
{
	Get().LoadPreloadAssets();
}

void UDefaultAssetManager::LoadSyncByPath(const FGameplayTag& AssetTag, const FSoftObjectPath& AssetPath)
{
	if (AssetPath.IsValid())
	{
		UObject* LoadedAsset = AssetPath.ResolveObject();
		if (LoadedAsset == nullptr)
		{
			if (UAssetManager::IsInitialized())
			{
				LoadedAsset = UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath, false);
			}
			else
			{
				LoadedAsset = AssetPath.TryLoad();
			}
		}

		if (LoadedAsset)
		{
			Get().AddLoadedAssetByAssetTag(AssetTag, LoadedAsset);
		}
		else
		{
			UE_LOG(LogAssetLoad, Fatal, TEXT("Failed to load asset [%s]"), *AssetPath.ToString());
		}
	}
}

void UDefaultAssetManager::LoadAsyncByLabel(const FGameplayTag& LabelTag, FAsyncLoadCompleteDelegate CompletedDelegate)
{
	if (UAssetManager::IsInitialized() == false)
	{
		UE_LOG(LogAssetLoad, Error, TEXT("AssetManager must be initialized"));
		return;
	}

	UInputPrimaryDataAsset* AssetData = Get().LoadedInputPrimaryDataAssets;
	check(AssetData);

	const FAssetSet& AssetSet = AssetData->GetAssetSetByLabelTag(LabelTag);
	for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
		LoadAsyncByPath(AssetEntry.AssetTag, AssetPath, CompletedDelegate);
	}
}

void UDefaultAssetManager::LoadAsyncByPath(const FGameplayTag& AssetTag, const FSoftObjectPath& AssetPath, FAsyncLoadCompleteDelegate CompletedDelegate)
{
	if (UAssetManager::IsInitialized() == false)
	{
		UE_LOG(LogAssetLoad, Error, TEXT("AssetManager must be initialized"));
		return;
	}

	if (AssetPath.IsValid())
	{
		if (UObject* LoadedAsset = AssetPath.ResolveObject())
		{
			Get().AddLoadedAssetByAssetTag(AssetTag, LoadedAsset);
		}
		else
		{
			TArray<FSoftObjectPath> AssetPaths;
			AssetPaths.Add(AssetPath);

			TSharedPtr<FStreamableHandle> Handle = GetStreamableManager().RequestAsyncLoad(AssetPaths);

			Handle->BindCompleteDelegate(FStreamableDelegate::CreateLambda([AssetTag, AssetPath, CompleteDelegate = MoveTemp(CompletedDelegate)]()
				{
					UObject* LoadedAsset = AssetPath.ResolveObject();
					Get().AddLoadedAssetByAssetTag(AssetTag, LoadedAsset);
					if (CompleteDelegate.IsBound())
						CompleteDelegate.Execute(AssetTag, LoadedAsset);
				}));
		}
	}
}

void UDefaultAssetManager::LoadSyncByLabel(const FGameplayTag& LabelTag)
{
	if (UAssetManager::IsInitialized() == false)
	{
		UE_LOG(LogAssetLoad, Fatal, TEXT("AssetManager must be initialized"));
		return;
	}

	UInputPrimaryDataAsset* AssetData = Get().LoadedInputPrimaryDataAssets;
	check(AssetData);

	const FAssetSet& AssetSet = AssetData->GetAssetSetByLabelTag(LabelTag);
	for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
		LoadSyncByPath(AssetEntry.AssetTag, AssetPath);
	}
}

void UDefaultAssetManager::LoadPreloadAssets()
{
	if (LoadedInputPrimaryDataAssets)
		return;

	UInputPrimaryDataAsset* AssetData = nullptr;
	FPrimaryAssetType PrimaryAssetType(UInputPrimaryDataAsset::StaticClass()->GetFName());
	TSharedPtr<FStreamableHandle> Handle = LoadPrimaryAssetsWithType(PrimaryAssetType);

	if (Handle.IsValid())
	{
		Handle->WaitUntilComplete(0.f, false);
		AssetData = Cast<UInputPrimaryDataAsset>(Handle->GetLoadedAsset());
	}

	if (AssetData)
	{
		LoadedInputPrimaryDataAssets = AssetData;
		LoadSyncByLabel(GamePlayTags::LabelLoadStatic);
	}
	else
	{
		UE_LOG(LogAssetLoad, Fatal, TEXT("Failed to load AssetData [%s]."), *PrimaryAssetType.ToString());
	}
}

void UDefaultAssetManager::AddLoadedAssetByAssetTag(const FGameplayTag& AssetTag, const UObject* Asset)
{
	if (AssetTag.IsValid() && Asset)
	{
		//FScopeLock LoadedAssetsLock(&LoadedAssetsCritical);

		if (AssetTagToLoadedAsset.Contains(AssetTag) == false)
		{
			AssetTagToLoadedAsset.Add(AssetTag, Asset);
		}
	}
}