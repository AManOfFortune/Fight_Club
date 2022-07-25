#include "Ability.h"

Ability::Ability()
{
	//Standard ability is a single target damage ability
	setName("Standard Ability");
	setDescription("Hits a single enemy with 30 damage");
	setSkillCost(5.f);
	setTargetType('s');
	setTargets('a');
	setEffectType('d');
	setAffectBy(30.f);
	setStatusEffects(new std::map<char, int>());
}

Ability::~Ability()
{
	delete _statusEffects;
}

void Ability::setName(std::string name)
{
	_name = name;
}

void Ability::setDescription(std::string description)
{
	_description = description;
}

void Ability::setSkillCost(float skillCost)
{
	_skillCost = skillCost;
}

void Ability::setTargetType(char targetType)
{
	if (targetType != 's' && targetType != 'm')
		_targetType = 's';
	else
		_targetType = targetType;
}

void Ability::setTargets(char targets)
{
	if (targets != 't' && targets != 's' && targets != 'e' && targets != 'a')
		_targets = 'e';
	else
		_targets = targets;
}

void Ability::setEffectType(char effectType)
{
	if (effectType != 'd' && effectType != 'h' && effectType != 'n')
		_effectType = 'd';
	else
		_effectType = effectType;
}

void Ability::setAffectBy(float affectBy)
{
	_affectBy = affectBy;
}

void Ability::setStatusEffects(std::map<char, int>* statusEffects)
{
	_statusEffects = statusEffects;
}

std::string Ability::getName()
{
	return _name;
}

std::string Ability::getDescription()
{
	return _description;
}

float Ability::getSkillCost()
{
	return _skillCost;
}

char Ability::getTargetType()
{
	return _targetType;
}

char Ability::getTargets()
{
	return _targets;
}

char Ability::getEffectType()
{
	return _effectType;
}

float Ability::getAffectBy()
{
	return _affectBy;
}

std::map<char, int>* Ability::getStatusEffects()
{
	return _statusEffects;
}

void Ability::addStatusEffects(std::map<char, int> addedStatusEffects)
{
	std::map<char, int>::iterator itr;

	for (itr = addedStatusEffects.begin(); itr != addedStatusEffects.end(); itr++) {
		getStatusEffects()->insert(std::pair<char, int>(itr->first, itr->second));
	}
}
