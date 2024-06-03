#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "NativeGamePlayTags.h"
#include "AnimNotifySendPlayEvent.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UAnimNotifySendPlayEvent : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotifySendPlayEvent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void Notify(
		USkeletalMeshComponent* MeshComp, 
		UAnimSequenceBase* Animation, 
		const FAnimNotifyEventReference& EventReference
	) override;

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag EventTag;
};
