// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyZone.generated.h"

class USphereComponent;

UCLASS()
class PORTFOLIO_API AEnemyZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(Category = Collision, EditAnywhere)
	TObjectPtr<USphereComponent> SphereCollision;

protected:
	UPROPERTY(Category = Monster, EditAnywhere)
	TObjectPtr<AActor> Monster;

protected:
	int TotalPlayerCount = 0;


protected:
	UFUNCTION()
	virtual void OnBeginOverlapped(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, 
		const FHitResult& SweepResult
	);

	UFUNCTION()
	virtual void OnEndOverlapped(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
	);


};
