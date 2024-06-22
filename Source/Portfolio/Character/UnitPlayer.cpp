// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/UnitPlayer.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AUnitPlayer::AUnitPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());
	SpringArmComponent->TargetArmLength = 200.f;
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 88.f));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->bInheritYaw = true;
	SpringArmComponent->bInheritRoll = false;

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	if (CapsuleComp != nullptr)
	{
		CapsuleComp->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
		//CapsuleComp->SetCollisionProfileName(TEXT("Player"));
		CapsuleComp->UpdateCollisionProfile();
	}
}

// Called when the game starts or when spawned
void AUnitPlayer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AUnitPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShowTargeted();
}

// Called to bind functionality to input
void AUnitPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUnitPlayer::SetSringArmLength(const float& Length)
{
	SpringArmComponent->TargetArmLength = std::max(std::min(MaxSpringArmLength, Length), MinSpringArmLength);
}

void AUnitPlayer::ShowTargeted()
{
	if (TargetToAttack)
	{
		DrawDebugSphere(GetWorld(), TargetToAttack->GetActorLocation(), 150.f, 15, FColor::Magenta);
	}
}
