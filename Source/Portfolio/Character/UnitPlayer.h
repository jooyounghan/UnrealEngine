// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Creature.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

#include "UnitPlayer.generated.h"

UCLASS()
class PORTFOLIO_API AUnitPlayer : public ACreature
{
	GENERATED_BODY()
	
public:
	AUnitPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(Category = ViewPoint, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArmComponent;
	UPROPERTY(Category = ViewPoint, VisibleAnywhere, BlueprintReadOnly)
	float MaxSpringArmLength = 500.f;
	UPROPERTY(Category = ViewPoint, VisibleAnywhere, BlueprintReadOnly)
	float MinSpringArmLength = 200.f;

public:
	UFUNCTION()
	inline float GetSpringArmLength() { return SpringArmComponent->TargetArmLength; }
	UFUNCTION()
	void SetSringArmLength(const float& Length);

protected:
	void ShowTargeted();

public:
	UPROPERTY(Category = ViewPoint, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> CameraComponent;
};
