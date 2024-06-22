#include "Character/Creature.h"
#include "Util/DefaultGamePlayTags.h"
#include "Interface/StateInterface.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Log/LogChannel.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Stat/StatBar.h"

ACreature::ACreature()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->RotationRate.SetComponentForAxis(EAxis::Z, 540.f);
	}

	HpBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	MpBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("MPBar"));
	HpBarComponent->SetupAttachment(RootComponent);
	MpBarComponent->SetupAttachment(RootComponent);

	ConstructorHelpers::FClassFinder<UUserWidget> StatBarWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Stat/WBP_StatBar.WBP_StatBar_C'"));
	if (StatBarWidgetClass.Succeeded())
	{
		HpBarComponent->SetWidgetClass(StatBarWidgetClass.Class);
		HpBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
		HpBarComponent->SetDrawAtDesiredSize(true);
		HpBarComponent->SetRelativeLocation(FVector(0.f, 0.f, 150.f));

		MpBarComponent->SetWidgetClass(StatBarWidgetClass.Class);
		MpBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
		MpBarComponent->SetDrawAtDesiredSize(true);
		MpBarComponent->SetRelativeLocation(FVector(0.f, 0.f, 140.f));
	}

}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();

	SetHpBarStyle();
	SetMpBarStyle();
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

void ACreature::HandleGamePlayEvent(FGameplayTag EventTag)
{
	CharacterState->HandleGamePlayEvent(this, EventTag);
}

bool ACreature::IsNearForAttacking()
{
	return TargetToAttack != nullptr ? (TargetToAttack->GetActorLocation() - GetActorLocation()).Length() < 250.f : false;
}

void ACreature::SetHpBarStyle()
{
	if (HpBarComponent)
	{
		UStatBar* HpBarWidget = Cast<UStatBar>(HpBarComponent->GetUserWidgetObject());
		if (HpBarWidget)
		{
			HpBarWidget->SetColorAndOpacity(FLinearColor(0.9f, 0.02f, 0.1f, 1.f));
			HpBarWidget->SetRatio(1.f);
		}
	}
}

void ACreature::SetMpBarStyle()
{
	if (MpBarComponent)
	{
		UStatBar* MpBarWidget = Cast<UStatBar>(MpBarComponent->GetUserWidgetObject());
		if (MpBarWidget)
		{
			MpBarWidget->SetColorAndOpacity(FLinearColor(0.1f, 0.02f, 0.9f, 1.f));
			MpBarWidget->SetRatio(1.f);
		}
	}

}


void ACreature::SetTargetToAttack(ACreature* Target)
{
	TargetToAttack = Target;
}

void ACreature::ResetTargetToAttack()
{
	TargetToAttack = nullptr;
	StopAnimMontage(AttackAnimMontage);
}