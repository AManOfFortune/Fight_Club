#pragma once

//ADD NEW CHARACTER
//1. Create new .h file, add it to the "Characters" folder
//2. Create the class inside the file, use other characters as a template
//3. Include the .h file in Team.h
//4. Increase the NUMBER_OF_CHARACTERS
#define NUMBER_OF_CHARACTERS 5
//5. Team.cpp
//   - initAllCharacters()
//6. Add <Name>|0|0 to stats.txt file


//ADD NEW ABILITY
//1. Create new .h file, add it to the "Abilities" folder
//2. Create the class inside the file, use other abilities as a template
//3. Include the .h file in Character.h

//Changing this does not work
#define NUMBER_OF_TEAMS 2
//Changing this works
#define CHARS_PER_TEAM 2
//Changing this almost works but it doesn't
#define ABILITIES_PER_CHAR 2

//Changing this works but doesn't affect much
#define MAX_NAME_LENGTH 20
//Changing this works
#define AI_SPEED_IN_MILLISECONDS 3000

#define RED_BG "\033[41m"
#define GREEN_TEXT "\033[32m"
#define GREY_BG "\033[100m"
#define RESET "\033[m"

//ADD NEW STATUS EFFECT
//1. Add the status effect to the enum
//2. Game.cpp
//   - specialActionOnAddStatus()
//   - statusAction()
//   - specialActionOnRemoveStatus()
//3. Character.cpp
//   - printStatusEffects()

enum status_effects {
	BURNING = 'b',
	POISONED = 'p',
	STUNNED = 's',
	RAGE = 'r'
};