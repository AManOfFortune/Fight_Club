#pragma once
#include "Ability.h"
class Sex :
	public Ability
{
public:
	Sex() {
		setName("Sex");
		setDescription("Spread love... and herpes");
		setSkillCost(2.f);
		setTargetType('s');
		setTargets('t');
		setEffectType('h');
		setAffectBy(35.f);

		std::map<char, int> statusEffects;
		statusEffects.insert(std::pair<char, int>(POISONED, 2));
		addStatusEffects(statusEffects);
	};
};