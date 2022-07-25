#pragma once
#include "Ability.h"
class BrokenElbow :
    public Ability
{
public:
    BrokenElbow() {
		setName("I don't care that you broke your elbow");
		setDescription("The ultimate stun");
		setSkillCost(8.f);
		setTargetType('m');
		setTargets('e');
		setEffectType('d');
		setAffectBy(10.f);

		std::map<char, int> statusEffects;
		statusEffects.insert(std::pair<char, int>(STUNNED, 3));
		addStatusEffects(statusEffects);
    }
};