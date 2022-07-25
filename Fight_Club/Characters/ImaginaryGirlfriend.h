#pragma once
#include "Character.h"
class ImaginaryGirlfriend :
    public Character
{
public:
    ImaginaryGirlfriend() {
        setName("Imaginary Girlfriend");
        setDescription("No one else loves you, but she does");

        setHp(75.f);
        setMaxSkillCharge(15.f);
        setSkillCharge(0.f);
        setSkillChargeOnHit(2.f);
        setBaseDamage(20.f);

        Ability* abilities[ABILITIES_PER_CHAR]{ NULL };
        abilities[0] = new Sex();
        abilities[1] = new Medicine();

        setAbilities(abilities);
    };
};