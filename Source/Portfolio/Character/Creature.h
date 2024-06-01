// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/TargetingInterface.h"
#include "Creature.generated.h"

class IStateInterface;

UCLASS()
class PORTFOLIO_API ACreature : public ACharacter, public ITargetingInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACreature();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	IStateInterface* CharacterState;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void Target() override;
	virtual void UnTarget() override;

protected:
	UPROPERTY(Category = Target, VisibleAnywhere)
	TObjectPtr<ACreature> TargetToAttack;

public:
	UFUNCTION()
	void SetTargetToAttack(ACreature* Target);
	UFUNCTION()
	void ResetTargetToAttack();
	UFUNCTION()
	inline ACreature* GetTargetToAttack() { return TargetToAttack; }

public:
	UPROPERTY(Category = Target, BlueprintReadOnly)
	float MaxEnemyFindDistance = 10000.f;

public:
	bool IsNearForAttacking(const double& Distance);

protected:
	bool bIsAttackable = false;

public:
	void DefaultAttack();

public:
	UPROPERTY(Category = Animation, EditAnywhere)
	TObjectPtr<UAnimMontage> AttackAnimMontage;
};
