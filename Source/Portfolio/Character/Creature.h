// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Interface/TargetingInterface.h"
#include "Creature.generated.h"

class IStateInterface;
struct FGameplayTag;

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
	UPROPERTY(BlueprintReadOnly)
	TScriptInterface<IStateInterface> CharacterState;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(Category = ViewPoint, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(Category = ViewPoint, VisibleAnywhere, BlueprintReadOnly)
	float MaxSpringArmLength = 500.f;
	UPROPERTY(Category = ViewPoint, VisibleAnywhere, BlueprintReadOnly)
	float MinSpringArmLength = 200.f;
public:
	UFUNCTION()
	inline float GetSpringArmLength() { return SpringArmComponent->TargetArmLength; }
	UFUNCTION()
	void SetSringArmLength(const float& Length);

public:
	UPROPERTY(Category = ViewPoint, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;


public:
	virtual void Target() override;
	virtual void UnTarget() override;

public:
	void HandleGamePlayEvent(FGameplayTag EventTag);

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
	bool IsNearForAttacking();

protected:
	bool bIsAttackable = false;

public:
	void DefaultAttack();

public:
	UPROPERTY(Category = Animation, EditAnywhere)
	TObjectPtr<UAnimMontage> AttackAnimMontage;
};
