// Fill out your copyright notice in the Description page of Project Settings.

#include "Zone/EnemyZone.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemyZone::AEnemyZone()
	: Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollsion"));
	SphereCollision->SetupAttachment(RootComponent);

	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionProfileName(TEXT("Zone"));
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->UpdateCollisionProfile();
}

// Called when the game starts or when spawned
void AEnemyZone::BeginPlay()
{
	Super::BeginPlay();
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlapped);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlapped);
}

// Called every frame
void AEnemyZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyZone::OnBeginOverlapped(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Black, TEXT("Enter"));
}

void AEnemyZone::OnEndOverlapped(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex
)
{
	GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Black, TEXT("Exit"));
}
