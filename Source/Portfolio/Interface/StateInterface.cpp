#include "Interface/StateInterface.h"

#include "Character/Creature.h"

#include "Controller/DefaultPlayerController.h"

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"

void IStateInterface::DefaultHandleKeyMove(
	ACreature* Creature, 
	ADefaultPlayerController* Controller,
	const FVector2D& Movement
)
{
	Controller->StopMovement();

	const double Yaw = Creature->CameraComponent->GetComponentRotation().Yaw;

	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0, Yaw, 0));
	const FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0, Yaw, 0));

	Creature->ResetTargetToAttack();
	Creature->AddMovementInput(ForwardVector, Movement.X);
	Creature->AddMovementInput(RightVector, Movement.Y);
}

void IStateInterface::DefaultHandleMouseClickingMove(
	ACreature* Creature, 
	ADefaultPlayerController* Controller
)
{
	Controller->StopMovement();
	Creature->ResetTargetToAttack();

	FHitResult Hit;
	bool bHitSuccess = Controller->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);

	if (bHitSuccess)
	{
		FVector WorldDirection = (Hit.Location - Creature->GetActorLocation()).GetSafeNormal();
		Creature->AddMovementInput(WorldDirection);
	}

}

void IStateInterface::DefaultHandleMouseClickMove(
	ACreature* Creature, 
	ADefaultPlayerController* Controller, 
	UNiagaraSystem* ClickFX
)
{
	FHitResult Hit;
	bool bHitSuccess = Controller->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);

	if (bHitSuccess)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, Hit.Location);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(Controller, ClickFX, Hit.Location);
	}
}

