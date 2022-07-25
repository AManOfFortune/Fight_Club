#pragma once
#include "Character.h"
class Bernhard :
    public Character
{
public:
    Bernhard() {
        setName("Prof. Bernhard");
        setDescription("I know you are beginners, so we're going to take it slow. Anyway, so this is a pointer...");

        setSkillCharge(3.f);
        setBaseDamage(10.f);

        Ability* abilities[ABILITIES_PER_CHAR]{ NULL };
        abilities[0] = new FirePunch();
        abilities[1] = new Pointers();

        setAbilities(abilities);
    };
};