#include "Arbiter.h"

#include "Game.h"

Arbiter::Arbiter()
{
}

void Arbiter::addCharacterToHeap(Character* newChar)
{
	characterHeap.add(newChar);
}

void Arbiter::removeCharacterFromHeap(Character* charToRemove)
{
	characterHeap.remove(charToRemove);
}

void Arbiter::registerTeamsToHeap()
{
	Game* gamePtr = Game::getInstance();


}