#include "UI/Stat/StatBar.h"
#include "Components/ProgressBar.h"

UStatBar::UStatBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UStatBar::Initialize()
{
	Super::Initialize();
	return false;
}

void UStatBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void UStatBar::SetRatio(float Percent)
{
	if (StatProgressBar)
	{
		StatProgressBar->SetPercent(Percent);
	}
}
