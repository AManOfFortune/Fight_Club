#pragma once
#include "Character.h"
class YourMom : 
	public Character
{
public:
    YourMom() {
        setName("Your Mom");
        setDescription("So fat NASA considers her a planet");

        setHp(130.f);
        setMaxSkillCharge(10.f);
        setSkillCharge(0.f);
        setSkillChargeOnHit(2.f);
        setBaseDamage(5.f);

        Ability* abilities[ABILITIES_PER_CHAR]{ NULL };
        abilities[0] = new Talk();
        abilities[1] = new Tits();

        setAbilities(abilities);
    };
};

