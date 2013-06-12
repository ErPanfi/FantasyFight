#include "Arbiter.h"
#include "Game.h"

#include "Character.h"
#include "Action.h"

Arbiter::Arbiter()
	: m_fatigueReductionCounter(0)
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
		currChar -> incFatigue();
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

void Arbiter::reduceFatigueOfEveryone()
{
	++m_fatigueReductionCounter %= FATIGUE_REDUCTION_PERIOD;	//epic code line, but nothing like  --(*p)++

	if(!m_fatigueReductionCounter)
	{
		int offset = characterHeap.top() -> getFatigue();

		Game* gamePtr = Game::getInstance();
		Team* currTeam = gamePtr -> getTeam(Game::TeamEnum::LEFT);
		for(int j = 0; j < currTeam -> getTeamSize(); j++)
			currTeam -> m_teamMembers[j] -> incFatigue(-offset);

		currTeam = gamePtr -> getTeam(Game::TeamEnum::RIGHT);
		for(int j = 0; j < currTeam -> getTeamSize(); j++)
			currTeam -> m_teamMembers[j] -> incFatigue(-offset);
	}
}

Character* Arbiter::nextCharacterToAct() 
{
	reduceFatigueOfEveryone();
	return characterHeap.top();
}

void Arbiter::prepareCharacterForTurn(Character* theCharacter)		//preliminary for turn start
{
	theCharacter -> incMP();
}

void Arbiter::evolveEffectsOnCharacter(Character* theCharacter)		//evolution of active effects
{

}

void Arbiter::registerCharacterNewAction(Character* theCharacter)	//ask the character for a new action and store it
{
	Action* newAction = theCharacter -> decideNextAction();


}

void Arbiter::handleActiveAttacks(Character* theCharacter)			//charge character action and eventually perform the attack
{
}

void Arbiter::endCharacterTurn(Character* theCharacter)				//prepare character for turn end
{
}
