#pragma once
#include "Team.h"

class Game
{
public:
	//Setter
	void setTeams(Team* teams[NUMBER_OF_TEAMS]);
	void setCurrentTeam(Team* currentTeam);
	void setCharCurrentlyFighting(Character* charCurrentlyFighting);

	//Getter
	Team** getTeams();
	Team* getCurrentTeam();
	Character* getCharCurrentlyFighting();

	//Public functions
	void start();

private:
	//Variables
	Team* _teams[NUMBER_OF_TEAMS];
	Team* _currentTeam;
	Character* _charCurrentlyFighting;

	//Functions
	int showTitleScreen();
	void mainGameLoop();

	void initTeams(int mode);
	void deleteTeams();

	void printFightScreenStats();
	void printFightScreenCharacter(Character* character, int charNumber, bool charsTurn);
	
	void doAction(int whatAction);
	void useAbility(Ability* ability);
	void specialActionOnAddStatus(std::map<char, int>::iterator addedStatus, Character* target);
	void statusAction();
	void specialActionOnRemoveStatus(std::map<char, int>::iterator removedStatus, Character* target);

	int askAction();
	int askTarget(char validTargets);
	int askMode();

	Team* getNextTeam();
	Team* getNextTeam(Team* currentTeam);
	void nextCharacter();

	bool multipleTeamsAlive();

	void writeStats(Team* winningTeam);
	void getStats();
};