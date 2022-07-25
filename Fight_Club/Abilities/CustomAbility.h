#pragma once
#include "Ability.h"
class CustomAbility :
	public Ability
{
public:
	CustomAbility(std::string name, float skillCost, char targetType, char targets, char effectType, float affectBy) {
		setName(name);
		setDescription("Custom Ability");
		setSkillCost(skillCost);
		setTargetType(targetType);
		setTargets(targets);
		setEffectType(effectType);
		setAffectBy(affectBy);
	};
};