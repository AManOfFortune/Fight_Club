#pragma once
#include "Character.h"
class Custom :
    public Character
{
public:
    Custom(std::string name, float hp, float startingSkillCharge, float maxSkillCharge, float skillChargeOnHit, float baseDamage, Ability* abilities[ABILITIES_PER_CHAR]) {
		setName(name);
		setHp(hp);
		setSkillCharge(startingSkillCharge);
		setMaxSkillCharge(maxSkillCharge);
		setSkillChargeOnHit(skillChargeOnHit);
		setBaseDamage(baseDamage);
		setAbilities(abilities);
    };
};