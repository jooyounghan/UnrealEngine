#include "Animation/AnimNotify/AnimNotifySendPlayEvent.h"
#include "Character/Creature.h"
#include "Interface/StateInterface.h"

UAnimNotifySendPlayEvent::UAnimNotifySendPlayEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAnimNotifySendPlayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACreature* CreatureFrom = Cast<ACreature>(MeshComp->GetOwner());
	if (CreatureFrom)
	{
		CreatureFrom->HandleGamePlayEvent(EventTag);
	}
}


