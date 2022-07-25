#include "Team.h"
#include <iostream>

Team::Team(bool isPlayerControlled, int teamNumber)
{
	//Initializes the all characters array
	initAllCharacters();

	//Sets the player controlled flag
	setIsPlayerControlled(isPlayerControlled);

	//Initializes the characters array
	Character* characters[CHARS_PER_TEAM]{ NULL };

	for (int i = 0; i < CHARS_PER_TEAM; i++) {
		characters[i] = selectCharacter(this->isPlayerControlled(), teamNumber, i+1, characters);
	}

	setCharacters(characters);
}

Team::~Team()
{
	//Deletes all characters from heap
	for (int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
		delete _allCharacters[i];
	}
}

void Team::setCharacters(Character* characters[CHARS_PER_TEAM])
{
	for (int i = 0; i < CHARS_PER_TEAM; i++) {
		_characters[i] = characters[i];
	}
}

void Team::setIsPlayerControlled(bool isPlayerControlled)
{
	_isPlayerControlled = isPlayerControlled;
}

Character* Team::getCharacterAtIndex(int index)
{
	return _characters[index];
}

bool Team::isPlayerControlled()
{
	return _isPlayerControlled;
}

void Team::initAllCharacters()
{
	_allCharacters[0] = new DonaldTrump();
	_allCharacters[1] = new YourMom();
	_allCharacters[2] = new Bernhard();
	_allCharacters[3] = new Nerd();
	_allCharacters[4] = new ImaginaryGirlfriend();
}

bool Team::isDead()
{
	int deadChars = 0;
	for (int i = 0; i < CHARS_PER_TEAM; i++) {
		if (!getCharacterAtIndex(i)->isAlive()) {
			deadChars++;
		}
	}

	if (deadChars == CHARS_PER_TEAM)
		return true;

	return false;
}

Character** Team::getAllCharacters()
{
	return _allCharacters;
}

Character* Team::selectCharacter(bool playerControlled, int teamNumber, int charNumber, Character* alreadyPicked[CHARS_PER_TEAM])
{
	//Loops as long as player does not confirm his choice
	while (true) {
		system("cls");

		int choice = 0;

		if (playerControlled) {
			std::cout << "Team " << teamNumber << "\nSelect character number " << charNumber << ":\n" << std::endl;

			for (int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
				std::cout << i + 1 << " - " << getAllCharacters()[i]->getName() << std::endl;
			}
			std::cout << NUMBER_OF_CHARACTERS + 1 << " - Custom" << std::endl;

			bool duplicate = false;
			do {
				std::cout << "\nChoose Number: ";
				std::cin >> choice;

				duplicate = false;
				for (int i = 0; i < CHARS_PER_TEAM; i++) {
					if (getAllCharacters()[choice - 1] == alreadyPicked[i]) {
						std::cout << "Duplicate character not possible!" << std::endl;
						duplicate = true;
						break;
					}
				}
			} while ((choice <= 0 || choice > NUMBER_OF_CHARACTERS + 1) || duplicate);

			system("cls");
		}
		else {
			bool duplicate = false;
			do {
				choice = (rand() % NUMBER_OF_CHARACTERS) + 1;

				duplicate = false;
				for (int i = 0; i < CHARS_PER_TEAM; i++) {
					if (getAllCharacters()[choice - 1] == alreadyPicked[i]) {
						duplicate = true;
						break;
					}
				}
			} while (duplicate);
			
		}

		//If the choice is not random or custom, and the player confirms his choice, return the selected character
		if ((playerControlled && choice != NUMBER_OF_CHARACTERS + 1) && confirmChoice(getAllCharacters()[choice - 1]))
			return getAllCharacters()[choice - 1];
		//If the choice is random, return the random character
		if (!playerControlled)
			return getAllCharacters()[choice - 1];
		//If the choice was custom, create the custom character and return it
		if (choice == NUMBER_OF_CHARACTERS + 1)
			return createCustomCharacter();
	}

	//Not necessary but compiler cries when its gone so I'll just leave it here
	return nullptr;
}

bool Team::confirmChoice(Character* character)
{
	std::cout << character->getName() << std::endl;

	std::cout << "\n\"" << character->getDescription() << "\"" << std::endl;

	std::cout << "\nHp: " << character->getHp() << std::endl;
	std::cout << "Damage: " << character->getBaseDamage() << std::endl;

	std::cout << "\nSkill charge on hit: " << character->getSkillChargeOnHit() << std::endl;
	std::cout << "Max Skill charge: " << character->getMaxSkillCharge() << std::endl;
	std::cout << "Starting Skill charge: " << character->getSkillCharge() << std::endl;

	std::cout << "\nStatus Effects:" << std::endl;
	if (character->getStatusEffects()->size())
		character->printStatusEffects(character->getStatusEffects());
	else
		std::cout << "None" << std::endl;
	
	std::cout << std::endl;

	std::cout << "\nAbilities: " << std::endl;

	for (int i = 0; i < ABILITIES_PER_CHAR; i++) {
		Ability* ability = character->getAbilityAtIndex(i);

		std::string targetType = ability->getTargetType() == 's' ? "Single" : "Multiple";

		std::string targets = "";
		switch (ability->getTargets())
		{
		case 't':
			targets = "Team";
			break;
		case 'e':
			targets = "Enemies";
			break;
		case 's':
			targets = "Self";
			break;
		case 'a':
			targets = "All";
		}

		std::string effectType = "";
		switch (ability->getEffectType())
		{
		case 'd':
			effectType = "Damage";
			break;
		case 'h':
			effectType = "Heal";
			break;
		case 'n':
			effectType = "None";
			break;
		}

		std::cout << "\n"<< i + 1 << " - # " << ability->getName() << std::endl;
		std::cout << "    # \"" << ability->getDescription() << "\"" << std::endl;
		std::cout << "    # Skill cost: " << ability->getSkillCost() << std::endl;
		std::cout << "    # Target type: " << targetType << std::endl;
		std::cout << "    # Targets: " << targets << std::endl;
		std::cout << "    # Effect type: " << effectType << std::endl;
		std::cout << "    # Affect by: " << ability->getAffectBy() << std::endl;
		std::cout << "    # Status effects: ";
		character->printStatusEffects(ability->getStatusEffects());
		std::cout << std::endl;
	}

	std::cout << GREEN_TEXT << "\n1 - Choose" << RESET << std::endl;
	std::cout << "2 - Back\n" << std::endl;

	int choice = 0;
	do {
		std::cout << "Choose: ";
		std::cin >> choice;
	} while (choice <= 0 || choice > 2);

	system("cls");

	if (choice == 1)
		return true;

	return false;
}

Character* Team::createCustomCharacter()
{
	std::string name;
	float hp = 0;
	float startingSkillCharge = 0;
	float maxSkillCharge = 0;
	float skillChargeOnHit = 0;
	float baseDamage = 0;
	Ability* abilities[ABILITIES_PER_CHAR]{ NULL };

	std::cout << "Name: ";
	std::cin >> name;
	
	std::cout << "Hp: ";
	std::cin >> hp;

	std::cout << "Damage: ";
	std::cin >> baseDamage;

	std::cout << "Starting Skill Charge: ";
	std::cin >> startingSkillCharge;

	std::cout << "Maximum Skill Charge: ";
	std::cin >> maxSkillCharge;

	std::cout << "Skill Charge on Hit: ";
	std::cin >> skillChargeOnHit;

	for (int i = 0; i < ABILITIES_PER_CHAR; i++) {
		abilities[i] = createCustomAbility(i + 1);
	}

	system("cls");

	return new Custom(name, hp, startingSkillCharge, maxSkillCharge, skillChargeOnHit, baseDamage, abilities);
}

Ability* Team::createCustomAbility(int number)
{
	std::string name;
	float skillCost = 5;
	char targetType = 's';
	char targets = 'e';
	char effectType = 'd';
	float affectBy = 10.f;

	std::cout << "\nCreate your ability number " << number << ":" << std::endl;

	do {
		std::cout << "Name (no spaces allowed): ";
		std::cin >> name;
	} while (name.length() <= 0);

	do {
		std::cout << "Skill cost: ";
		std::cin >> skillCost;
	} while (skillCost < 0);

	do {
		std::cout << "(s)ingle or (m)ulitple targets: ";
		std::cin >> targetType;
	} while (targetType != 's' && targetType != 'm');

	do {
		std::cout << "Valid Targets are (t)eam, (s)elf, (e)nemies or (a)ll: ";
		std::cin >> targets;
	} while (targets != 't' && targets != 's' && targets != 'e' && targets != 'a');

	do {
		std::cout << "Deal (d)amage, (h)ealing or (n)o direct effect: ";
		std::cin >> effectType;
	} while (effectType != 'd' && effectType != 'h' && effectType != 'n');

	std::cout << "If you heal/deal damage, how much: ";
	std::cin >> affectBy;

	return new CustomAbility(name, skillCost, targetType, targets, effectType, affectBy);
}
