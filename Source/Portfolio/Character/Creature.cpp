#include "Character/Creature.h"

ACreature::ACreature()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ACreature::Target()
{
	bIsTargeted = true;
}

void ACreature::UnTarget()
{
	bIsTargeted = false;
}

bool ACreature::IsNearForAttacking()
{
	return TargetToAttack != nullptr ? (TargetToAttack->GetActorLocation() - GetActorLocation()).Length() < 250.f : false;
}

void ACreature::DefaultAttack()
{
	// State ÂÊÀ¸·Î!
	if (bIsAttackable && AttackAnimMontage)
	{
		bIsAttackable = false;
		const FString AttackFormatter = FString(TEXT("Attack_{0}"));
		const FString AttackFormatted = FString::Format(*AttackFormatter, { rand() % AttackAnimMontage->GetNumSections() });
		PlayAnimMontage(AttackAnimMontage, 1.0f, *AttackFormatted);
	}
}


void ACreature::SetTargetToAttack(ACreature* Target)
{
	TargetToAttack = Target;
	bIsAttackable = true;
}

void ACreature::ResetTargetToAttack()
{
	TargetToAttack = nullptr;
	bIsAttackable = false;
	StopAnimMontage(AttackAnimMontage);
}