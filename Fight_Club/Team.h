#pragma once
#include "Config.h"

#include "Characters/DonaldTrump.h"
#include "Characters/YourMom.h"
#include "Characters/Bernhard.h"
#include "Characters/Nerd.h"
#include "Characters/ImaginaryGirlfriend.h"
#include "Characters/Custom.h"

class Team
{
public:
	//Constructor
	Team(bool isPlayerControlled, int teamNumber);
	~Team();

	//Setter
	void setCharacters(Character* characters[CHARS_PER_TEAM]);
	void setIsPlayerControlled(bool isPlayerControlled);

	//Getter
	Character* getCharacterAtIndex(int index);
	bool isPlayerControlled();

	//Functions
	void initAllCharacters();
	bool isDead();

private:
	//Variables
	Character* _allCharacters[NUMBER_OF_CHARACTERS];
	Character* _characters[CHARS_PER_TEAM];
	bool _isPlayerControlled;

	//Functions
	Character** getAllCharacters();
	Character* selectCharacter(bool playerControlled, int teamNumber, int charNumber, Character* alreadyPicked[CHARS_PER_TEAM]);
	bool confirmChoice(Character* character);
	Character* createCustomCharacter();
	Ability* createCustomAbility(int number);
};