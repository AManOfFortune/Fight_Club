#pragma once
#include "Character.h"
class DonaldTrump :
    public Character
{
public:
    DonaldTrump() {
        setName("Donald Trump");
        setDescription("Very stupid but makes that an advantage somehow");

        setHp(120.f);
        setMaxSkillCharge(15.f);
        setSkillCharge(0.f);
        setSkillChargeOnHit(3.f);
        setBaseDamage(15.f);

        Ability* abilities[ABILITIES_PER_CHAR] { NULL };
        abilities[0] = new Talk();
        abilities[1] = new MAGA();

        setAbilities(abilities);

        std::map<char, int> statusEffects;
        statusEffects.insert(std::pair<char, int>(RAGE, 2));
        addStatusEffects(statusEffects);
    };
};