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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(BlueprintReadOnly)
	TScriptInterface<IStateInterface> CharacterState;

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

public:
	UPROPERTY(Category = Animation, EditAnywhere)
	TObjectPtr<UAnimMontage> AttackAnimMontage;

protected:
	UPROPERTY(Category = Stat, EditAnywhere)
	int32 Hp = 100;
	UPROPERTY(Category = Stat, EditAnywhere)
	int32 MaxHp = 100;

protected:
	UPROPERTY(Category = Stat, EditAnywhere)
	int32 Mp = 100;
	UPROPERTY(Category = Stat, EditAnywhere)
	int32 MaxMp = 100;

protected:
	UPROPERTY(Category = Stat, EditAnywhere)
	TObjectPtr<class UWidgetComponent> HpBarComponent;

	UPROPERTY(Category = Stat, EditAnywhere)
	TObjectPtr<class UWidgetComponent> MpBarComponent;

protected:
	virtual void SetHpBarStyle();
	virtual void SetMpBarStyle();
};
