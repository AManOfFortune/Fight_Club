#pragma once
#include <string>
#include <map>
#include <iterator>

class Ability
{
public:
	//Constructor
	Ability();
	~Ability();

	//Getters & Setters
	void setName(std::string name);
	void setDescription(std::string description);
	void setSkillCost(float skillCost);
	void setTargetType(char targetType);
	void setTargets(char targets);
	void setEffectType(char effectType);
	void setAffectBy(float affectBy);
	//Set status effects also exists, but is private

	std::string getName();
	std::string getDescription();
	float getSkillCost();
	char getTargetType();
	char getTargets();
	char getEffectType();
	float getAffectBy();
	std::map<char, int>* getStatusEffects();

	//Functions
	void addStatusEffects(std::map<char, int> addedStatusEffects);

private:
	std::string _name;
	std::string _description;

	//Skill cost
	float _skillCost;

	//Targets
	//(s)ingle target, (m)ultitarget
	char _targetType;
	//(t)eam, (s)elf, (e)nemies, (a)ll
	char _targets;

	//Effects
	//(d)amage, (h)ealing, (n)either
	char _effectType;
	//Depending on type, either heal or deal damage by...
	float _affectBy;
	//Dictionary of status effects with duration
	std::map<char, int>* _statusEffects;

	//Is a setter, but should only be called from this class, all children and others should call addStatusEffects
	void setStatusEffects(std::map<char, int>* statusEffects);
};