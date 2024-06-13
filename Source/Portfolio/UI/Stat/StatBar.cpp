#include "UI/Stat/StatBar.h"
#include "Components/ProgressBar.h"

UStatBar::UStatBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
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
