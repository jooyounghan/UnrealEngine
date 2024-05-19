// Fill out your copyright notice in the Description page of Project Settings.


#include "Util/DefaultGamePlayTags.h"

namespace GamePlayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Input,			"Input");
	UE_DEFINE_GAMEPLAY_TAG(InputAction,		"Input.Action");
	UE_DEFINE_GAMEPLAY_TAG(InputActionMove, "Input.Action.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputActionTurn, "Input.Action.Turn");
	UE_DEFINE_GAMEPLAY_TAG(InputActionJump, "Input.Action.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputActionAttack, "Input.Action.Attack");

	UE_DEFINE_GAMEPLAY_TAG(LabelLoadStatic, "Label.Load.Static");
	UE_DEFINE_GAMEPLAY_TAG(LabelLoadDynamic, "Label.Load.Dynamic");
}