// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DefaultPlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Creature.h"
#include "Animation/AnimMontage.h"

UDefaultPlayerAnimInstance::UDefaultPlayerAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDefaultPlayerAnimInstance::NativeInitializeAnimation()
{
	Creature = Cast<ACreature>(GetOwningActor());
	if (Creature)
	{
		CharacterMovement = Creature->GetCharacterMovement();
	}
}

void UDefaultPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Creature == nullptr || Creature->CharacterState == nullptr) return;
	if (CharacterMovement == nullptr) return;

	Velocity = CharacterMovement->Velocity;
	GroundSpeed = Velocity.Size2D();
	bShouldMove = GroundSpeed > 3.f;
	CharacterState = Creature->CharacterState->GetState();
}
