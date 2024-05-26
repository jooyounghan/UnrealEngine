// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGamePlayTags.h"

namespace GamePlayTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputSkill);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputSkill1);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputSkill2);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputSkill3);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputSkill4);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputSkillSpace);

		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputAction);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputActionMoveByKey);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputActionMoveByMouse);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputActionZoom);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputActionTurn);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputActionAttack);

		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputAdditive);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputAdditiveMouseMiddle);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputAdditiveCtrl);

		UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTargeting);
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTargetingCtrl);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Label);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(LabelLoad);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(LabelLoadStatic);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(LabelLoadDynamic);
}