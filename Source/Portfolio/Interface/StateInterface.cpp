#include "Interface/StateInterface.h"
#include "Character/Creature.h"
#include "Controller/DefaultPlayerController.h"


void IStateInterface::DefaultHandleMove(
	ACreature* Creature, 
	ADefaultPlayerController* Controller,
	const FVector2D& Movement, 
	const FVector& ForwardVector, 
	const FVector& RightVector
)
{
	Controller->StopMovement();
	Creature->AddMovementInput(ForwardVector, Movement.X);
	Creature->AddMovementInput(RightVector, Movement.Y);

}

void IStateInterface::DefaultHandleMove(
	ACreature* Creature, 
	ADefaultPlayerController* Controller,
	const FVector& Direction
)
{
	Creature->AddMovementInput(Direction);
}

