#ifndef FANTASYFIGHT_ARBITER_H
#define FANTASYFIGHT_ARBITER_H

#include "Heap.h"
#include "Game.h"
#include "Character.h"

class Arbiter
{
private:

	//accessible only through game
	friend class Game;	//make creation pf arbiter by game access
	Arbiter();
	//TODO implement copy ctor, dtor and = restrictions

	static const int MAX_HEAP_SIZE = 16;

	Heap<Character*, MAX_HEAP_SIZE, Character::compareFatigue > m_characterHeap;

	//fatigue reduction handling method
	static const int FATIGUE_REDUCTION_PERIOD = 100;
	int	 m_fatigueReductionCounter;
	void reduceFatigueOfEveryone();

	//turn cycle methods
	Character* nextCharacterToAct();							//select next character to act
	void prepareCharacterForTurn(Character* theCharacter);		//preliminary for turn start
	void evolveEffectsOnCharacter(Character* theCharacter);		//evolution of active effects
	void registerCharacterNewAction(Character* theCharacter);	//ask the character for a new action and store it
	void handleActiveAttacks(Character* theCharacter);			//charge character action and eventually perform the attack
	void endCharacterTurn(Character* theCharacter);				//prepare character for turn end

	//victory flag
	Game::TeamEnum m_winningTeam;
	void checkVictoryConditions();

public:

	void registerTeamsToHeap();
	void addCharacterToHeap(Character* newChar);
	void removeCharacterFromHeap(Character* charToRemove);

	bool performTurnCycle();		//perform the whole game turn and return true if the game can continue
	
	Game::TeamEnum getWinningTeam() const { return m_winningTeam; }

};

#endif