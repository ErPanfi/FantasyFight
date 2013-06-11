#ifndef FANTASYFIGHT_ARBITER_H
#define FANTASYFIGHT_ARBITER_H

#include "Character.h"
#include "Heap.h"

class Arbiter
{
private:

	static const int MAX_HEAP_SIZE = 16;

	Heap<Character*, MAX_HEAP_SIZE, Character::compareFatigue > characterHeap;

public:
	Arbiter();

	void registerTeamsToHeap();
	void addCharacterToHeap(Character* newChar);
	void removeCharacterFromHeap(Character* newChar);
};

#endif