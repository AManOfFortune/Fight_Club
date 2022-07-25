#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <fstream>

void Game::setTeams(Team* teams[NUMBER_OF_TEAMS])
{
	for (int i = 0; i < NUMBER_OF_TEAMS; i++) {
		_teams[i] = teams[i];
	}
}

void Game::setCurrentTeam(Team* currentTeam)
{
	_currentTeam = currentTeam;
}

void Game::setCharCurrentlyFighting(Character* charCurrentlyFighting)
{
	_charCurrentlyFighting = charCurrentlyFighting;
}

Team** Game::getTeams()
{
	return _teams;
}

Team* Game::getCurrentTeam()
{
	return _currentTeam;
}

Character* Game::getCharCurrentlyFighting()
{
	return _charCurrentlyFighting;
}

void Game::start()
{
	bool quit = false;

	while (!quit) {
		switch (showTitleScreen()) {
			//Play
			case 1:
				initTeams(askMode());
				mainGameLoop();
				deleteTeams();
				break;
			//Show stats
			case 2:
				getStats();
				break;
			//Quit
			case 3:
				quit = true;
				break;
		}
	}
}

void Game::mainGameLoop()
{
	//Main game loop
	while (multipleTeamsAlive()) {
		//Prints all character stats
		printFightScreenStats();
		//If character can fight, asks (or chooses a random) action, does that action
		if (getCharCurrentlyFighting()->canFight()) {
			doAction(askAction());
			//If an AI fought, sleep so player can read the message and see what it did
			if(!getCurrentTeam()->isPlayerControlled())
				Sleep(AI_SPEED_IN_MILLISECONDS);
		}
		else
			Sleep(1000);
		//Does the status effect effects
		statusAction();
		//Current fighting character ++
		nextCharacter();
		//Clear the screen
		system("cls");
	}

	//After game loop finishes, check which team won & print message
	for (int i = 0; i < NUMBER_OF_TEAMS; i++) {
		if (!getTeams()[i]->isDead()) {
			system("cls");
			std::cout << "#################" << std::endl;
			std::cout << "#  Team " << i + 1 << " won!  #" << std::endl;
			std::cout << "#################\n" << std::endl;
			system("pause");
			
			//Write the stats
			writeStats(getTeams()[i]);
			break;
		}
	}
}

void Game::initTeams(int mode)
{
	Team* teams[NUMBER_OF_TEAMS]{ NULL };

	switch (mode) {
		//Player vs AI
		case 1:
			for (int i = 0; i < NUMBER_OF_TEAMS; i++) {
				if (i % 2)
					teams[i] = new Team(false, i + 1);
				else
					teams[i] = new Team(true, i + 1);
			}
			break;
		//Player vs Player
		case 2:
			for (int i = 0; i < NUMBER_OF_TEAMS; i++) {
				teams[i] = new Team(true, i + 1);
			}
			break;
		//AI vs AI
		case 3:
			for (int i = 0; i < NUMBER_OF_TEAMS; i++) {
				teams[i] = new Team(false, i + 1);
			}
			break;
	}
	//Save the teams in class variable
	setTeams(teams);
	//Set the current team to be team 1
	setCurrentTeam(getTeams()[0]);
	//The first character of the first team starts
	setCharCurrentlyFighting(getCurrentTeam()->getCharacterAtIndex(0));
}

void Game::deleteTeams()
{
	for (int i = 0; i < NUMBER_OF_TEAMS; i++) {
		delete _teams[i];
	}
}

void Game::printFightScreenStats()
{
	for (int j = 0; j < NUMBER_OF_TEAMS; j++) {
		std::string type = getTeams()[j]->isPlayerControlled() ? "Player" : "AI";
		std::cout << "Team " << j+1 << " (" << type << ")\n" << std::endl;
		//Print team
		for (int i = 0; i < CHARS_PER_TEAM; i++) {
			printFightScreenCharacter(getTeams()[j]->getCharacterAtIndex(i), i + 1 + (j * CHARS_PER_TEAM), getCharCurrentlyFighting() == getTeams()[j]->getCharacterAtIndex(i));
			std::cout << std::endl;
		}
	}
}

void Game::printFightScreenCharacter(Character* character, int charNumber, bool charsTurn)
{
	//Print top line of namebox + healthbar
	if (charsTurn)
		std::cout << GREY_BG;
	for (int k = 0; k < MAX_NAME_LENGTH + 8; k++) {
		std::cout << "#";
	}
	if (charsTurn)
		std::cout << RESET;

	std::cout << " " << RED_BG;
	//Calculation is being done so that only for every two points of hp a space is printed (the healthbar would be too long otherwise)
	for (int k = 0; k < (character->getHp() / 2); k++) {
		std::cout << " ";
	}
	std::cout << RESET << std::endl;

	//Print character name + fill up rest of box with space so that all boxes are same size + print character skillcharge
	if (charsTurn)
		std::cout << GREY_BG;
	std::cout << "#";
	if (charsTurn)
		std::cout << RESET;
	std::cout << " " << charNumber << " - ";

	std::cout << character->getName();

	for (int k = 0; k < MAX_NAME_LENGTH - character->getName().length(); k++) {
		std::cout << " ";
	}

	std::cout << " ";
	if (charsTurn)
		std::cout << GREY_BG;
	std::cout << "#";
	if (charsTurn)
		std::cout << RESET;
	std::cout << " ";

	for (int k = 0; k < character->getMaxSkillCharge(); k++) {
		if (k < character->getSkillCharge())
			std::cout << "(" << GREEN_TEXT << "o" << RESET << ")";
		else
			std::cout << "( )";
	}
	std::cout << std::endl;

	//Print bottom line of namebox + Status effects
	if (charsTurn)
		std::cout << GREY_BG;
	for (int k = 0; k < MAX_NAME_LENGTH + 8; k++) {
		std::cout << "#";
	}
	if (charsTurn)
		std::cout << RESET;

	std::cout << " ";
	character->printStatusEffects(character->getStatusEffects());
	std::cout << std::endl;
}

void Game::doAction(int whatAction)
{
	switch (whatAction) {
		//Basic attack
		case 1:
			getNextTeam()->getCharacterAtIndex(askTarget('e') - 1)->takeDamage(getCharCurrentlyFighting()->getBaseDamage());
			getCharCurrentlyFighting()->increaseSkillChargeBy(getCharCurrentlyFighting()->getSkillChargeOnHit());
			break;
		//Ability
		default:
			useAbility(getCharCurrentlyFighting()->getAbilityAtIndex(whatAction - 2));
			getCharCurrentlyFighting()->decreaseSkillChargeBy(getCharCurrentlyFighting()->getAbilityAtIndex(whatAction - 2)->getSkillCost());
			break;
	}
}

void Game::useAbility(Ability* ability)
{
	//Single target ability
	if (ability->getTargetType() == 's') {
		//Evaluate target
		int targetIndex = 0;
		Character* target = NULL;
		switch (ability->getTargets()) {
			case 't':
				target = getCurrentTeam()->getCharacterAtIndex(askTarget('t') - 1);
				break;
			case 's':
				target = getCharCurrentlyFighting();
				break;
			case 'e':
				target = getNextTeam()->getCharacterAtIndex(askTarget('e') - 1);
				break;
			case 'a':
				targetIndex = askTarget('a') - 1;
				if (targetIndex > CHARS_PER_TEAM)
					target = getNextTeam()->getCharacterAtIndex(targetIndex - CHARS_PER_TEAM);
				else
					target = getCurrentTeam()->getCharacterAtIndex(targetIndex);
				break;
		}

		//Do action depending on type
		switch (ability->getEffectType()) {
			case 'd':
				target->takeDamage(ability->getAffectBy());
				break;
			case 'h':
				target->setHp(target->getHp() + ability->getAffectBy());
				break;
			case 'n':
				break;
		}

		//If the ability adds status effects, add them
		if (ability->getStatusEffects()->size()) {
			//Creates a copy so we can append the effect not as a pointer to the ability (also the funciton addStatusEffect needs a regular map, not a map pointer)
			std::map<char, int> copy;

			//Copies the effects to the target, also does a special action for certain effects on that character
			for (std::map<char, int>::iterator itr = ability->getStatusEffects()->begin(); itr != ability->getStatusEffects()->end(); itr++) {
				specialActionOnAddStatus(itr, target);
				copy.insert(std::pair<char, int>(itr->first, itr->second));
			}

			target->addStatusEffects(copy);
		}
	}
	//Multitarget ability
	else if (ability->getTargetType() == 'm') {
		//If we attack all loop over both teams, otherwise loop only over affected team
		if (ability->getTargets() == 't' || ability->getTargets() == 'a') {
			for (int i = 0; i < CHARS_PER_TEAM; i++) {
				//Do action depending on type
				switch (ability->getEffectType()) {
				case 'd':
					getCurrentTeam()->getCharacterAtIndex(i)->takeDamage(ability->getAffectBy());
					break;
				case 'h':
					getCurrentTeam()->getCharacterAtIndex(i)->setHp(getCurrentTeam()->getCharacterAtIndex(i)->getHp() + ability->getAffectBy());
					break;
				case 'n':
					break;
				}

				//If the ability adds status effects, add them
				if (ability->getStatusEffects()->size()) {
					//Creates a copy so we can append the effect not as a pointer to the ability (also the funciton addStatusEffect needs a map, not a map pointer)
					std::map<char, int> copy;

					std::map<char, int>::iterator itr;
					for (itr = ability->getStatusEffects()->begin(); itr != ability->getStatusEffects()->end(); itr++) {
						specialActionOnAddStatus(itr, getCurrentTeam()->getCharacterAtIndex(i));
						copy.insert(std::pair<char, int>(itr->first, itr->second));
					}

					getCurrentTeam()->getCharacterAtIndex(i)->addStatusEffects(copy);
				}
			}
		}
		if (ability->getTargets() == 'e' || ability->getTargets() == 'a') {
			for (int i = 0; i < CHARS_PER_TEAM; i++) {
				//Do action depending on type
				switch (ability->getEffectType()) {
				case 'd':
					getNextTeam()->getCharacterAtIndex(i)->takeDamage(ability->getAffectBy());
					break;
				case 'h':
					getNextTeam()->getCharacterAtIndex(i)->setHp(getNextTeam()->getCharacterAtIndex(i)->getHp() + ability->getAffectBy());
					break;
				case 'n':
					break;
				}

				//If the ability adds status effects, add them
				if (ability->getStatusEffects()->size()) {
					//Creates a copy so we can append the effect not as a pointer to the ability (also the funciton addStatusEffect needs a regular map, not a map pointer)
					std::map<char, int> copy;

					std::map<char, int>::iterator itr;
					for (itr = ability->getStatusEffects()->begin(); itr != ability->getStatusEffects()->end(); itr++) {
						specialActionOnAddStatus(itr, getNextTeam()->getCharacterAtIndex(i));
						copy.insert(std::pair<char, int>(itr->first, itr->second));
					}

					getNextTeam()->getCharacterAtIndex(i)->addStatusEffects(copy);
				}
			}
		}
	}
}

void Game::specialActionOnAddStatus(std::map<char, int>::iterator addedStatus, Character* target)
{
	switch (addedStatus->first) {
	case STUNNED:
		target->canFight(false);
		break;
	case RAGE:
		target->setBaseDamage(target->getBaseDamage() + (addedStatus->second * 10));
		target->setSkillChargeOnHit(target->getSkillChargeOnHit() + (addedStatus->second * 1));
		break;
	default:
		break;
	}
}

void Game::statusAction()
{
	//Wierd loop (itr does not get incremented normally), done bc of a wierd issue with itrator not iterating if increment is done in for-loop
	for (std::map<char, int>::iterator itr = getCharCurrentlyFighting()->getStatusEffects()->begin(); itr != getCharCurrentlyFighting()->getStatusEffects()->end(); ) {
		bool remove = false;

		switch (itr->first) {
		case BURNING:
			getCharCurrentlyFighting()->takeDamage(10.f);
			remove = true;
			break;
		case POISONED:
			getCharCurrentlyFighting()->takeDamage(static_cast<float>(itr->second)*3);
			remove = true;
			break;
		case STUNNED:
			remove = true;
			break;
		case RAGE:
			remove = false;
			break;
		}

		if (remove) {
			if (itr->second <= 1) {
				specialActionOnRemoveStatus(itr, getCharCurrentlyFighting());
			}
			getCharCurrentlyFighting()->removeStatusEffect(itr++);
		}
		else {
			++itr;
		}
	}
}

void Game::specialActionOnRemoveStatus(std::map<char, int>::iterator removedStatus, Character* target)
{
	switch (removedStatus->first) {
	case STUNNED:
		target->canFight(true);
		break;
	case RAGE:
		target->setBaseDamage(target->getBaseDamage() - (removedStatus->second * 10));
		target->setSkillChargeOnHit(target->getSkillChargeOnHit() - (removedStatus->second * 1));
		break;
	default:
		break;
	}
}

int Game::askAction()
{
	int action = 0;

	//If currently a player controlled character is fighting let the player choose an action
	if (getCurrentTeam()->isPlayerControlled()) {
		std::cout << "What do you want to do?\n" << std::endl;
		std::cout << "1 - Attack" << std::endl;
		
		for (int i = 0; i < ABILITIES_PER_CHAR; i++) {
			std::cout << i + 2 << " - Ability: " << getCharCurrentlyFighting()->getAbilityAtIndex(i)->getName() << " (" << getCharCurrentlyFighting()->getAbilityAtIndex(i)->getSkillCost() << ")" << std::endl;
		}

		std::cout << std::endl;

		bool invalid = false;
		do {
			invalid = false;

			std::cout << "Choose: ";
			std::cin >> action;

			//If ability cost is bigger than player skill charge repeat loop
			if ((action > 1 && action <= ABILITIES_PER_CHAR + 1) && getCharCurrentlyFighting()->getAbilityAtIndex(action-2)->getSkillCost() > getCharCurrentlyFighting()->getSkillCharge()) {
				std::cout << "Not enough skill charge for this ability!" << std::endl;
				invalid = true;
			}
		} while ((action <= 0 || action > ABILITIES_PER_CHAR + 1) || invalid);
	}
	//Otherwise choose a random action
	else {

		bool invalid = false;
		do {
			invalid = false;

			action = (rand() % (ABILITIES_PER_CHAR + 1)) + 1;

			//If ability cost is bigger than player skill charge repeat loop
			if (action > 1 && getCharCurrentlyFighting()->getAbilityAtIndex(action-2)->getSkillCost() > getCharCurrentlyFighting()->getSkillCharge())
				invalid = true;

		} while (invalid);

		//Prints a message to make it more clear what the AI does
		//Second part of message inside askTarget()
		switch (action) {
		case 1:
			std::cout << getCharCurrentlyFighting()->getName() << " attacks ";
			break;
		default:
			std::cout << getCharCurrentlyFighting()->getName() << " uses " << getCharCurrentlyFighting()->getAbilityAtIndex(action-2)->getName() << " on ";
			break;
		}
	}

	return action;
}

//THIS FUNCTION SUCKS ASS, CUZ IT ONLY WORKS FOR 2 TEAMS... BUT IT DOES WORK SO I'LL LEAVE IT FOR FUTURE ME TO FIX
int Game::askTarget(char validTargets)
{
	int target = 0;
	int firstValidTarget = 0;
	int lastValidTarget = 0;

	//Very stupid way of doing it, only works for 2 teams!!!
	switch (validTargets) {
		//Team
		case 't':
			if (getCurrentTeam() == getTeams()[0]) {
				firstValidTarget = 1;
				lastValidTarget = CHARS_PER_TEAM;
			}
			else {
				firstValidTarget = CHARS_PER_TEAM + 1;
				lastValidTarget = CHARS_PER_TEAM * 2;
			}
			break;
		//Enemies
		case 'e':
			if (getCurrentTeam() == getTeams()[0]) {
				
				firstValidTarget = CHARS_PER_TEAM + 1;
				lastValidTarget = CHARS_PER_TEAM * NUMBER_OF_TEAMS;
			}
			else {
				firstValidTarget = 1;
				lastValidTarget = CHARS_PER_TEAM;
			}
			break;
		//All
		case 'a':
			firstValidTarget = 1;
			lastValidTarget = CHARS_PER_TEAM * NUMBER_OF_TEAMS;
			break;
	}

	//If character is player controlled let him choose a target, otherwise choose a random target
	if (getCurrentTeam()->isPlayerControlled()) {
		do {
			std::cout << "Target number (" << firstValidTarget << " - " << lastValidTarget << "): ";
			std::cin >> target;
		} while (target < firstValidTarget || target > lastValidTarget);
	}
	else {
		bool alive = true;
		do {
			target = (rand() % lastValidTarget) + 1;

			//STUPID
			if (target > CHARS_PER_TEAM)
				alive = getTeams()[1]->getCharacterAtIndex(target - CHARS_PER_TEAM - 1)->isAlive();
			else
				alive = getTeams()[0]->getCharacterAtIndex(target - 1)->isAlive();

		} while (target < firstValidTarget || !alive);

		//STUPID TOO
		if (target > CHARS_PER_TEAM)
			std::cout << getTeams()[1]->getCharacterAtIndex(target - CHARS_PER_TEAM - 1)->getName() << "!";
		else
			std::cout << getTeams()[0]->getCharacterAtIndex(target - 1)->getName() << "!";
	}

	//JESUS CHRIST THIS IS PAINFUL
	switch (validTargets) {
		//Team
		case 't':
			if (getCurrentTeam() == getTeams()[0])
				return target;
			else
				return target - CHARS_PER_TEAM;
		//Enemies
		case 'e':
			if (getCurrentTeam() == getTeams()[0])
				return target - CHARS_PER_TEAM;
			else
				return target;
		default:
			break;
	}

	return target;
}

int Game::showTitleScreen()
{
	system("cls");

	std::cout << "#######################################################" << std::endl;
	std::cout << "#   ______ _       _     _      _____ _       _       #" << std::endl;
	std::cout << "#  |  ____(_)     | |   | |    / ____| |     | |      #" << std::endl;
	std::cout << "#  | |__   _  __ _| |__ | |_  | |    | |_   _| |__    #" << std::endl;
	std::cout << "#  |  __| | |/ _` | '_ \\| __| | |    | | | | | '_ \\   #" << std::endl;
	std::cout << "#  | |    | | (_| | | | | |_  | |____| | |_| | |_) |  #" << std::endl;
	std::cout << "#  |_|    |_|\\__, |_| |_|\\__|  \\_____|_|\\__,_|_.__/   #" << std::endl;
	std::cout << "#             __/ |                                   #" << std::endl;
	std::cout << "#            |___/                                    #" << std::endl;
	std::cout << "#######################################################" << std::endl;

	std::cout << "\n\n1 - Play" << std::endl;
	std::cout << "2 - Stats" << std::endl;
	std::cout << "3 - Quit\n" << std::endl;

	int choice = 0;

	do {
		std::cout << "Choose: ";
		std::cin >> choice;
	} while (choice <= 0 || choice > 3);

	return choice;
}

int Game::askMode()
{
	system("cls");

	std::cout << "Choose mode: \n" << std::endl;
	std::cout << "1 - Player vs AI" << std::endl;
	std::cout << "2 - Player vs Player" << std::endl;
	std::cout << "3 - AI vs AI\n" << std::endl;

	int choice = 0;

	do {
		std::cout << "Choose: ";
		std::cin >> choice;
	} while (choice <= 0 || choice > 3);

	system("cls");

	return choice;
}

Team* Game::getNextTeam()
{
	for (int i = 0; i < NUMBER_OF_TEAMS; i++) {
		if (getCurrentTeam() == getTeams()[i]) {
			if (i == NUMBER_OF_TEAMS - 1)
				return getTeams()[0];
			return getTeams()[i + 1];
		}
	}
	//Safety feature if current team somehow is not a team anymore
	return getTeams()[0];
}

Team* Game::getNextTeam(Team* currentTeam)
{
	for (int i = 0; i < NUMBER_OF_TEAMS; i++) {
		if (currentTeam == getTeams()[i]) {
			if (i == NUMBER_OF_TEAMS - 1)
				return getTeams()[0];
			return getTeams()[i + 1];
		}
	}
	//Safety feature if current team somehow is not a team anymore
	return getTeams()[0];
}

void Game::nextCharacter()
{
	bool found = false;
	for (int k = 0; k < NUMBER_OF_TEAMS && !found; k++) {
		for (int i = 0; i < CHARS_PER_TEAM && !found; i++) {
			//If the current character is not the last of a team, set the current character to the next one in that team
			if (i != CHARS_PER_TEAM - 1 && getCharCurrentlyFighting() == getTeams()[k]->getCharacterAtIndex(i)) {
				setCharCurrentlyFighting(getTeams()[k]->getCharacterAtIndex(i + 1));
				found = true;
			}
			//If the character is the last of a team, set current team to the next one and current character to the first one of that team
			else if (i == CHARS_PER_TEAM - 1 && getCharCurrentlyFighting() == getTeams()[k]->getCharacterAtIndex(i)) {
				setCurrentTeam(getNextTeam(getTeams()[k]));
				setCharCurrentlyFighting(getCurrentTeam()->getCharacterAtIndex(0));
				found = true;
			}
		}
	}
}

bool Game::multipleTeamsAlive()
{
	int numOfTeamsAlive = NUMBER_OF_TEAMS;

	for (int i = 0; i < NUMBER_OF_TEAMS; i++) {
		if(getTeams()[i]->isDead())
			numOfTeamsAlive--;
	}

	if (numOfTeamsAlive <= 1)
		return false;

	return true;
}

void Game::writeStats(Team* winningTeam)
{
	std::string newFileContent;

	//You might ask why one needs to read & write the same file seperately, and the answer is: fuck you.
	std::ifstream statsFile("stats.txt");
	if (statsFile.is_open())
	{
		//Loop for each character
		std::string line;
		while (getline(statsFile, line)) {
			std::string charName = line.substr(0, line.find("|"));
			line.erase(0, line.find("|") + 1);

			int wins = std::stoi(line.substr(0, line.find("|")));
			line.erase(0, line.find("|") + 1);

			int losses = std::stoi(line);

			//Check if character is in winning team
			bool won = false;
			for (int i = 0; i < CHARS_PER_TEAM; i++) {
				if (charName == winningTeam->getCharacterAtIndex(i)->getName()) {
					won = true;
				}
			}
			//Check if character is in losing teams
			bool lost = false;
			for (int i = 0; i < NUMBER_OF_TEAMS; i++) {
				for (int k = 0; k < CHARS_PER_TEAM; k++) {
					if (getTeams()[i] != winningTeam && charName == getTeams()[i]->getCharacterAtIndex(k)->getName()) {
						lost = true;
					}
				}
			}
			//Depending on if the character won || lost || didn't fight, add him to the newFileContent string
			if(won && !lost)
				newFileContent.append(charName + "|" + std::to_string(wins + 1) + "|" + std::to_string(losses) + "\n");
			else if (!won && lost)
				newFileContent.append(charName + "|" + std::to_string(wins) + "|" + std::to_string(losses + 1) + "\n");
			else if (won && lost)
				newFileContent.append(charName + "|" + std::to_string(wins + 1) + "|" + std::to_string(losses + 1) + "\n");
			else if (!won && !lost) {
				newFileContent.append(charName + "|" + std::to_string(wins) + "|" + std::to_string(losses) + "\n");
			}
		}

		statsFile.close();
	}
	else std::cout << "Unable to read file" << std::endl;

	//Completely unessecary if C++ wasn't utterly useless
	std::ofstream writeFile("stats.txt", std::ofstream::trunc);
	writeFile << newFileContent;
	writeFile.close();
}

void Game::getStats()
{
	system("cls");

	std::ifstream statsFile("stats.txt");

	if (statsFile.is_open())
	{
		//Loop for every line in stats file
		int charNumber = 0;
		std::string line;
		while (getline(statsFile, line)) {
			//Logic: Find name before "|", save it, then delete everything from line including "|", repeat for wins and losses
			std::string charName = line.substr(0, line.find("|"));
			line.erase(0, line.find("|") + 1);

			int wins = std::stoi(line.substr(0, line.find("|")));
			line.erase(0, line.find("|") + 1);

			int losses = std::stoi(line.substr(0, line.find("|")));

			std::cout << charName << ": " << wins << "W | " << losses << "L\n" << std::endl;
		}

		statsFile.close();
	}
	else std::cout << "Unable to open file" << std::endl;

	std::cout << std::endl;
	system("pause");
}