#pragma once
#include "Ability.h"
class Talk :
	public Ability
{
public:
	Talk() {
		setName("Talking");
		setDescription("Like 'em or hate 'em, but you do be spittin' straight bullshit right here");
		setSkillCost(4.f);
		setTargetType('m');
		setTargets('e');
		setEffectType('d');
		setAffectBy(15.f);

		std::map<char, int> statusEffects;
		statusEffects.insert(std::pair<char, int>(RAGE, 1));
		statusEffects.insert(std::pair<char, int>(STUNNED, 1));
		addStatusEffects(statusEffects);
	};
};