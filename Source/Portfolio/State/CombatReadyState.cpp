#include "State/CombatReadyState.h"

UCombatReadyState::UCombatReadyState()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatReadyState::BeginPlay()
{
	Super::BeginPlay();	
}

void UCombatReadyState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

ECreatureState UCombatReadyState::GetState() { return ECreatureState::CombatReady; };

bool UCombatReadyState::IsTransitable(ECreatureState NewState) { return false; }
void UCombatReadyState::HandleMove(const FVector& Location) {}
void UCombatReadyState::HandleAttack(const FVector& Location) {}