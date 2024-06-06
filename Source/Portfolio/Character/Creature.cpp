#include "Character/Creature.h"
#include "Util/DefaultGamePlayTags.h"
#include "Interface/StateInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

ACreature::ACreature()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());
	SpringArmComponent->TargetArmLength = 500.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->bInheritYaw = true;
	SpringArmComponent->bInheritRoll = false;

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->RotationRate.SetComponentForAxis(EAxis::Z, 540.f);
	}
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

void ACreature::SetSringArmLength(const float& Length)
{
	SpringArmComponent->TargetArmLength = std::max(std::min(MaxSpringArmLength, Length), MinSpringArmLength);
}

void ACreature::Target()
{
	bIsTargeted = true;
}

void ACreature::UnTarget()
{
	bIsTargeted = false;
}

void ACreature::HandleGamePlayEvent(FGameplayTag EventTag)
{
	CharacterState->HandleGamePlayEvent(this, EventTag);
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