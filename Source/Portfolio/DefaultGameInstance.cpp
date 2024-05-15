// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameInstance.h"
#include "DefaultAssetManager.h"

UDefaultGameInstance::UDefaultGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDefaultGameInstance::Init()
{
	Super::Init();
	UDefaultAssetManager::Initialize();
}

void UDefaultGameInstance::Shutdown()
{
	Super::Shutdown();
}
