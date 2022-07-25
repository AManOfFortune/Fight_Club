#pragma once
#include "Ability.h"
class Tits :
	public Ability
{
public:
	Tits() {
		setName("Fat tits");
		setDescription("I lost");
		setSkillCost(1.f);
		setTargetType('s');
		setTargets('e');
		setEffectType('d');
		setAffectBy(20.f);

		std::map<char, int> statusEffects;
		statusEffects.insert(std::pair<char, int>(POISONED, 3));
		addStatusEffects(statusEffects);
	};
};