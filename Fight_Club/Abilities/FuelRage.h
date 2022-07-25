#pragma once
#include "Ability.h"
class FuelRage :
	public Ability
{
public:
	FuelRage() {
		setName("Fuel Rage");
		setDescription("My blood is boiling");
		setSkillCost(1.f);
		setTargetType('s');
		setTargets('s');
		setEffectType('n');
		setAffectBy(0.f);

		std::map<char, int> statusEffects;
		statusEffects.insert(std::pair<char, int>(RAGE, 1));
		addStatusEffects(statusEffects);
	};
};