#ifndef FANTASYFIGHT_ARBITER_H
#define FANTASYFIGHT_ARBITER_H

#include "Heap.h"

#include "Character.h"

class Arbiter
{
private:

	static const int MAX_HEAP_SIZE = 16;

	Heap<Character*, MAX_HEAP_SIZE, Character::compareFatigue > characterHeap;

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

public:
	Arbiter();

	void registerTeamsToHeap();
	void addCharacterToHeap(Character* newChar);
	void removeCharacterFromHeap(Character* charToRemove);

	void performTurnCycle();		//perform the whole game turn
};

#endif