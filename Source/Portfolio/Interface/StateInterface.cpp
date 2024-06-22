#include "Interface/StateInterface.h"

#include "Character/Creature.h"
#include "Character/UnitPlayer.h"

#include "Controller/DefaultPlayerController.h"

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"

void IStateInterface::DefaultHandleKeyMove(
	AUnitPlayer* UnitPlayer,
	ADefaultPlayerController* Controller,
	const FVector2D& Movement
)
{
	Controller->StopMovement();

	
	const double Yaw = UnitPlayer->CameraComponent->GetComponentRotation().Yaw;

	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0, Yaw, 0));
	const FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0, Yaw, 0));

	UnitPlayer->ResetTargetToAttack();
	UnitPlayer->AddMovementInput(ForwardVector, Movement.X);
	UnitPlayer->AddMovementInput(RightVector, Movement.Y);
}

void IStateInterface::DefaultHandleMouseClickingMove(
	AUnitPlayer* UnitPlayer,
	ADefaultPlayerController* Controller
)
{
	Controller->StopMovement();
	UnitPlayer->ResetTargetToAttack();

	FHitResult Hit;
	bool bHitSuccess = Controller->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);

	if (bHitSuccess)
	{
		FVector WorldDirection = (Hit.Location - UnitPlayer->GetActorLocation()).GetSafeNormal();
		UnitPlayer->AddMovementInput(WorldDirection);
	}

}

void IStateInterface::DefaultHandleMouseClickMove(
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

