#pragma once
#include "Ability.h"
class Pointers :
	public Ability
{
public:
	Pointers() {
		setName("Pointers");
		setDescription("Death and despair.");
		setSkillCost(3.f);
		setTargetType('s');
		setTargets('e');
		setEffectType('n');
		setAffectBy(0.f);

		std::map<char, int> statusEffects;
		statusEffects.insert(std::pair<char, int>(STUNNED, 2));
		addStatusEffects(statusEffects);
	};
};