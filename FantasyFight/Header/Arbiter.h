#ifndef FANTASYFIGHT_ARBITER_H
#define FANTASYFIGHT_ARBITER_H

#include "Heap.h"

#include "Character.h"


class Arbiter
{
private:

	static const int MAX_HEAP_SIZE = 16;

	Heap<Character*, MAX_HEAP_SIZE, Character::compareFatigue > characterHeap;

	//turn cycle methods
	Character* nextCharacterToAct();


public:
	Arbiter();

	void registerTeamsToHeap();
	void addCharacterToHeap(Character* newChar);
	void removeCharacterFromHeap(Character* charToRemove);

	void performTurnCycle();
};

#endif