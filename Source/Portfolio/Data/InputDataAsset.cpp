// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/InputDataAsset.h"
#include "Log/LogChannel.h"

UInputAction* UInputDataAsset::FindInputActionByTag(const FGameplayTag& SpecificTag) const
{
	for (const auto& InputAction : InputActions)
	{
		if (InputAction.InputSpecificTag == SpecificTag)
		{
			return InputAction.InputAction;
		}
	}

	UE_LOG(LogAssetLoad, Fatal, TEXT("Can't Find the InputAction by Tag [%s]"), *SpecificTag.ToString());
	return nullptr;
}
