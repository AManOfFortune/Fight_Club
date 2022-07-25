#pragma once
#include "Config.h"
#include <string>

#include "Abilities/FirePunch.h"
#include "Abilities/BrokenElbow.h"
#include "Abilities/Pointers.h"
#include "Abilities/FuelRage.h"
#include "Abilities/Talk.h"
#include "Abilities/MAGA.h"
#include "Abilities/Tits.h"
#include "Abilities/Sex.h"
#include "Abilities/Medicine.h"
#include "Abilities/CustomAbility.h"

class Character
{
public:
	//Constructors & Destructors
	Character();
	~Character();

	//Getters & Setters
	std::string getName();
	std::string getDescription();

	float getHp();
	float getSkillCharge();
	float getMaxSkillCharge();
	float getSkillChargeOnHit();
	float getBaseDamage();
	std::map<char, int>* getStatusEffects();
	Ability* getAbilityAtIndex(int index);

	void setName(std::string name);
	void setDescription(std::string description);
	void setHp(float hp);
	void setSkillCharge(float skillCharge);
	void setMaxSkillCharge(float maxSkillCharge);
	void setSkillChargeOnHit(float skillChargeOnHit);
	void setBaseDamage(float baseDamage);
	void setAbilities(Ability* abilites[ABILITIES_PER_CHAR]);
	void setStatusEffects(std::map<char, int>* statusEffects);

	//Functions
	void takeDamage(float damage);
	void increaseSkillChargeBy(float increasedBy);
	void decreaseSkillChargeBy(float decreasedBy);
	void addStatusEffects(std::map<char, int> addedStatusEffects);
	void printStatusEffects(std::map<char, int>* statusEffects);
	void removeStatusEffect(std::map<char, int>::iterator statusEffect);
	bool isAlive();

	//Technically a getter & setter, but is one overloaded function
	bool canFight();
	void canFight(bool canFight);

private:
	std::string _name;
	std::string _description;

	float _hp;
	float _baseDamage;

	float _skillCharge;
	float _maxSkillCharge;
	float _skillChargeOnHit;

	std::map<char, int>* _statusEffects;
	Ability* _abilities[ABILITIES_PER_CHAR];

	bool _canFight;
};