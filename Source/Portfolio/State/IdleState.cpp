#include "State/IdleState.h"

UIdleState::UIdleState()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UIdleState::BeginPlay()
{
	Super::BeginPlay();	
}

void UIdleState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

ECreatureState UIdleState::GetState() { return ECreatureState::Idle; };

bool UIdleState::IsTransitable(ECreatureState NewState) { return false; }
void UIdleState::HandleMove(const FVector& Location) {}
void UIdleState::HandleAttack(const FVector& Location) {}