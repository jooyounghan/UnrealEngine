#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/StateInterface.h"
#include "CombatReadyState.generated.h"


//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS()
class PORTFOLIO_API UCombatReadyState : public UActorComponent, public IStateInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatReadyState();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual ECreatureState GetState() override;

public:
	virtual bool IsTransitable(ECreatureState NewState) override;
	virtual void HandleMove(const FVector& Location) override;
	virtual void HandleAttack(const FVector& Location) override;
};
