#pragma once
#include "Ability.h"
class Medicine :
	public Ability
{
public:
	Medicine() {
		setName("Schizophrenia medicine");
		setDescription("NoOooOoOOOoOoO!!!");
		setSkillCost(5.f);
		setTargetType('s');
		setTargets('t');
		setEffectType('n');
		setAffectBy(0.f);

		std::map<char, int> statusEffects;
		statusEffects.insert(std::pair<char, int>(RAGE, 3));
		addStatusEffects(statusEffects);
	};
};