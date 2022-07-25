#pragma once
#include "Character.h"
class Nerd :
    public Character
{
public:
    Nerd() {
        setName("Nerd");
        setDescription("Don't make me say it");

        setHp(100.f);
        setMaxSkillCharge(15.f);
        setSkillCharge(0.f);
        setSkillChargeOnHit(1.f);
        setBaseDamage(5.f);

        Ability* abilities[ABILITIES_PER_CHAR]{ NULL };
        abilities[0] = new FuelRage();
        abilities[1] = new BrokenElbow();

        setAbilities(abilities);
    };
};