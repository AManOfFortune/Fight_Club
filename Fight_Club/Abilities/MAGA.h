#pragma once
#include "Ability.h"
class MAGA :
	public Ability
{
public:
	MAGA() {
		setName("Make America great again");
		setDescription("Oh god, please no");
		setSkillCost(7.f);
		setTargetType('m');
		setTargets('a');
		setEffectType('d');
		setAffectBy(40.f);
	};
};