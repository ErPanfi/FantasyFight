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

	Team* currTeam = gamePtr -> getTeam(Game::TeamEnum::LEFT);
	for(int j = 0; j < currTeam -> getTeamSize(); j++)
	{
		Character* currChar = currTeam -> m_teamMembers[j];
		currChar->incFatigue();
		addCharacterToHeap(currChar);
	}

	currTeam = gamePtr -> getTeam(Game::TeamEnum::RIGHT);
	for(int j = 0; j < currTeam -> getTeamSize(); j++)
	{
		Character* currChar = currTeam -> m_teamMembers[j];
		currChar->incFatigue();
		addCharacterToHeap(currChar);
	}
}