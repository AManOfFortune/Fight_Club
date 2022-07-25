#include "Character.h"
#include <iostream>

Character::Character()
{
	setName("Undefined");
	setDescription("Undefined");
	setHp(100.f);
	setMaxSkillCharge(15.f);
	setSkillCharge(0.f);
	setSkillChargeOnHit(2.f);
	setBaseDamage(20.f);

	Ability* abilities[ABILITIES_PER_CHAR];
	for (int i = 0; i < ABILITIES_PER_CHAR; i++) {
		abilities[i] = new Ability();
	}
	setAbilities(abilities);
	setStatusEffects(new std::map<char, int>());
	canFight(true);
}

Character::~Character()
{
	//Delete all abilities from heap
	for (int i = 0; i < ABILITIES_PER_CHAR; i++) {
		delete _abilities[i];
	}

	//Delete status effect map from heap
	delete _statusEffects;
}

std::string Character::getName()
{
	return _name;
}

std::string Character::getDescription()
{
	return _description;
}

float Character::getHp()
{
	return _hp;
}

float Character::getSkillCharge()
{
	return _skillCharge;
}

float Character::getMaxSkillCharge()
{
	return _maxSkillCharge;
}

float Character::getSkillChargeOnHit()
{
	return _skillChargeOnHit;
}

float Character::getBaseDamage()
{
	return _baseDamage;
}

std::map<char, int>* Character::getStatusEffects()
{
	return _statusEffects;
}

Ability* Character::getAbilityAtIndex(int index)
{
	if (index >= ABILITIES_PER_CHAR)
		return _abilities[ABILITIES_PER_CHAR - 1];
	else
		return _abilities[index];
}

void Character::setName(std::string name)
{
	if (name.length() > MAX_NAME_LENGTH)
		_name = name.substr(0, MAX_NAME_LENGTH);
	else
		_name = name;
}

void Character::setDescription(std::string description)
{
	_description = description;
}

void Character::setHp(float hp)
{
	if (hp > 150)
		_hp = 150;
	else if (hp < 0)
		_hp = 0;
	else
		_hp = hp;
}

void Character::setSkillCharge(float skillCharge)
{
	if (skillCharge > getMaxSkillCharge())
		_skillCharge = getMaxSkillCharge();
	else if (skillCharge < 0)
		_skillCharge = 0;
	else
		_skillCharge = skillCharge;
}

void Character::setMaxSkillCharge(float maxSkillCharge)
{
	if (maxSkillCharge > 20)
		_maxSkillCharge = 20;
	else if (maxSkillCharge < 0)
		_maxSkillCharge = 0;
	else
		_maxSkillCharge = maxSkillCharge;
}

void Character::setSkillChargeOnHit(float skillChargeOnHit)
{
	if (skillChargeOnHit > getMaxSkillCharge())
		_skillChargeOnHit = getMaxSkillCharge();
	else if (skillChargeOnHit < 0)
		_skillChargeOnHit = 0;
	else
		_skillChargeOnHit = skillChargeOnHit;
}

void Character::setBaseDamage(float baseDamage)
{
	_baseDamage = baseDamage;
}

void Character::setAbilities(Ability* abilites[ABILITIES_PER_CHAR])
{
	for (int i = 0; i < ABILITIES_PER_CHAR; i++) {
		if (_abilities[i] != NULL)
			delete _abilities[i];

		_abilities[i] = abilites[i];
	}
}

void Character::setStatusEffects(std::map<char, int>* statusEffects)
{
	_statusEffects = statusEffects;
}

void Character::takeDamage(float damage)
{
	setHp(getHp() - damage);
}

void Character::increaseSkillChargeBy(float increasedBy)
{
	setSkillCharge(getSkillCharge() + increasedBy);
}

void Character::decreaseSkillChargeBy(float decreasedBy)
{
	setSkillCharge(getSkillCharge() - decreasedBy);
}

void Character::addStatusEffects(std::map<char, int> addedStatusEffects)
{
	std::map<char, int>::iterator itr;

	for (itr = addedStatusEffects.begin(); itr != addedStatusEffects.end(); itr++) {

		//If char already has a status effect that gets added, add the duration together
		if (getStatusEffects()->find(itr->first) != getStatusEffects()->end())
			getStatusEffects()->find(itr->first)->second = getStatusEffects()->find(itr->first)->second + itr->second;
		//Otherwise add the new status effect
		else
			getStatusEffects()->insert(std::pair<char, int>(itr->first, itr->second));
	}
}

void Character::printStatusEffects(std::map<char, int>* statusEffects)
{
	if (statusEffects->size()) {
		for (std::map<char, int>::iterator itr = statusEffects->begin(); itr != statusEffects->end(); itr++) {
			//Print seperator if multiple status effects are in place
			if (itr != statusEffects->begin())
				std::cout << " | ";
			//Print status effect messages
			if (itr->first == BURNING)
				std::cout << "BURNING [" << itr->second << "]";
			else if (itr->first == POISONED)
				std::cout << "POISONED [" << itr->second << "]";
			else if (itr->first == STUNNED)
				std::cout << "STUNNED [" << itr->second << "]";
			else if (itr->first == RAGE)
				std::cout << "RAGE [" << itr->second << "]";
		}
	}
}

void Character::removeStatusEffect(std::map<char, int>::iterator statusEffect)
{
	//If effect goes on longer than 1 round, duration--
	if (statusEffect->second > 1)
		statusEffect->second = statusEffect->second - 1;
	//If effect gets removed, remove it
	else {
		getStatusEffects()->erase(statusEffect->first);
	}
		
}

bool Character::isAlive()
{
	if (getHp() <= 0)
		return false;
	else
		return true;
}

bool Character::canFight()
{
	if (!isAlive())
		return false;

	return _canFight;
}

void Character::canFight(bool canFight) 
{
	if (!isAlive())
		_canFight = false;
	else
		_canFight = canFight;
}