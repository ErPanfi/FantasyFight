#include "Arbiter.h"

Arbiter::Arbiter()
{
}

void Arbiter::addCharacterToHeap(Character* newChar)
{
	characterHeap.add(newChar);
}