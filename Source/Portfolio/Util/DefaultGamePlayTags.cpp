// Fill out your copyright notice in the Description page of Project Settings.


#include "Util/DefaultGamePlayTags.h"

namespace GamePlayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Input,						"Input");
		UE_DEFINE_GAMEPLAY_TAG(InputSkill,					"Input.Skill");
			UE_DEFINE_GAMEPLAY_TAG(InputSkill1,					"Input.Skill.1");
			UE_DEFINE_GAMEPLAY_TAG(InputSkill2,					"Input.Skill.2");
			UE_DEFINE_GAMEPLAY_TAG(InputSkill3,					"Input.Skill.3");
			UE_DEFINE_GAMEPLAY_TAG(InputSkill4,					"Input.Skill.4");
			UE_DEFINE_GAMEPLAY_TAG(InputSkillSpace,				"Input.Skill.Space");

		UE_DEFINE_GAMEPLAY_TAG(InputAction,					"Input.Action");
			UE_DEFINE_GAMEPLAY_TAG(InputActionMoveByKey,		"Input.Action.MoveByKey");
			UE_DEFINE_GAMEPLAY_TAG(InputActionMoveByMouse,		"Input.Action.MoveByMouse");
			UE_DEFINE_GAMEPLAY_TAG(InputActionZoom,				"Input.Action.Zoom");
			UE_DEFINE_GAMEPLAY_TAG(InputActionTurn,				"Input.Action.Turn");
			UE_DEFINE_GAMEPLAY_TAG(InputActionAttack,			"Input.Action.Attack");

		UE_DEFINE_GAMEPLAY_TAG(InputAdditive,				"Input.Additive");
			UE_DEFINE_GAMEPLAY_TAG(InputAdditiveMouseMiddle,	"Input.Additive.MouseMiddle");
			UE_DEFINE_GAMEPLAY_TAG(InputAdditiveCtrl,			"Input.Additive.Ctrl");

		UE_DEFINE_GAMEPLAY_TAG(InputTargeting,				"Input.Targeting");
			UE_DEFINE_GAMEPLAY_TAG(InputTargetingCtrl,			"Input.Targeting.Ctrl");



	UE_DEFINE_GAMEPLAY_TAG(Label,						"Label");
		UE_DEFINE_GAMEPLAY_TAG(LabelLoad,					"Label.Load");
			UE_DEFINE_GAMEPLAY_TAG(LabelLoadStatic,				"Label.Load.Static");
			UE_DEFINE_GAMEPLAY_TAG(LabelLoadDynamic,			"Label.Load.Dynamic");
}