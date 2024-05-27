#include "State/MoveState.h"

UMoveState::UMoveState()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMoveState::BeginPlay()
{
	Super::BeginPlay();
	
}


void UMoveState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

ECreatureState UMoveState::GetState() { return ECreatureState::Move; };

bool UMoveState::IsTransitable(ECreatureState NewState) { return false; }
void UMoveState::HandleMove(const FVector& Location) {}
void UMoveState::HandleAttack(const FVector& Location) {}