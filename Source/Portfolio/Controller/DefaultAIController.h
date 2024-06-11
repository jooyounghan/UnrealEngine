#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DefaultAIController.generated.h"

UCLASS()
class PORTFOLIO_API ADefaultAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADefaultAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void BeginPlay() override;

public:
	virtual void OnPossess(APawn* InPawn) override;



};
