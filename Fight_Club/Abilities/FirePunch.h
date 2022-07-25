#pragma once
#include "Ability.h"
class FirePunch :
    public Ability
{
public:
    FirePunch() {
		setName("Fire Punch");
		setDescription("Just create an ability he said");
		setSkillCost(4.f);
		setTargetType('s');
		setTargets('e');
		setEffectType('d');
		setAffectBy(15.f);

		std::map<char, int> statusEffects;
		statusEffects.insert(std::pair<char, int>(BURNING, 2));
		addStatusEffects(statusEffects);
    };
};