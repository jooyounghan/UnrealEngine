#include "State/CombatingState.h"

UCombatingState::UCombatingState()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCombatingState::BeginPlay()
{
	Super::BeginPlay();
}

void UCombatingState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

ECreatureState UCombatingState::GetState() { return ECreatureState::Combating; };

bool UCombatingState::IsTransitable(ECreatureState NewState) { return false; }
void UCombatingState::HandleMove(const FVector& Location) {}
void UCombatingState::HandleAttack(const FVector& Location) {}