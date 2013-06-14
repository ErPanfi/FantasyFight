#include "Arbiter.h"
#include "Game.h"

#include "Character.h"
#include "Action.h"
#include "ActiveEffect.h"

#include "Global.h"
#include "Targetable.h"

#include <iostream>	//TODO remove

Arbiter::Arbiter()
	: m_fatigueReductionCounter(0)
	, m_winningTeam(Game::TeamEnum::COUNT_TEAMS)
{
}

void Arbiter::addCharacterToHeap(Character* newChar)
{
	m_characterHeap.add(newChar);
}

void Arbiter::removeCharacterFromHeap(Character* charToRemove)
{
	m_characterHeap.remove(charToRemove);
}

void Arbiter::registerTeamsToHeap()
{
	Game* gamePtr = Game::getInstance();

	Team::TeamCharacterList::Iterator beginIter = gamePtr -> getTeam(Game::TeamEnum::LEFT) -> getActiveMembersIterator();
	Team::TeamCharacterList::Iterator endIter = beginIter.endIterator();
	for(; beginIter != endIter; ++beginIter)
	{
		Character* currChar = *(beginIter.current());
		currChar -> incFatigue();
		addCharacterToHeap(currChar);
	}

	beginIter = gamePtr -> getTeam(Game::TeamEnum::RIGHT) -> getActiveMembersIterator();
	endIter = beginIter.endIterator();
	for(; beginIter != endIter; ++beginIter)
	{
		Character* currChar = *(beginIter.current());
		currChar->incFatigue();
		addCharacterToHeap(currChar);
	}
}

void Arbiter::reduceFatigueOfEveryone()
{
	++m_fatigueReductionCounter %= FATIGUE_REDUCTION_PERIOD;	//epic code line, but still n00b if compared to --(*p)++

	if(!m_fatigueReductionCounter)
	{
		int offset = -(m_characterHeap.top() -> getFatigue());

		Game* gamePtr = Game::getInstance();
		Team::TeamCharacterList::Iterator beginIter = gamePtr -> getTeam(Game::TeamEnum::LEFT) -> getActiveMembersIterator();
		Team::TeamCharacterList::Iterator endIter = beginIter.endIterator();
		for(; beginIter != endIter; ++beginIter)
		{
			Character* currChar = *(beginIter.current());
			currChar -> incFatigue(offset);
		}

		beginIter = gamePtr -> getTeam(Game::TeamEnum::RIGHT) -> getActiveMembersIterator();
		endIter = beginIter.endIterator();
		for(; beginIter != endIter; ++beginIter)
		{
			Character* currChar = *(beginIter.current());
			currChar -> incFatigue(offset);
		}
	}
}

//turn cycle methods
Character* Arbiter::nextCharacterToAct() 
{
	reduceFatigueOfEveryone();
	return m_characterHeap.top();
}

void Arbiter::prepareCharacterForTurn(Character* theCharacter)		//preliminary for turn start
{
	theCharacter -> incMP();
}

void Arbiter::evolveEffectsOnCharacter(Character* theCharacter)		//evolution of active effects
{
	Character::CharacterActiveEffectsList::Iterator effectIterator = theCharacter -> getActiveEffectsIterator();
	Character::CharacterActiveEffectsList::Iterator endEffectIterator = effectIterator.endIterator();
	for(; effectIterator != endEffectIterator; ++effectIterator)
	{
		ActiveEffect* currActiveEffect = *(effectIterator.current());
		currActiveEffect -> applyRecurringEffect();
		if(currActiveEffect -> canBeRemoved())
		{
			
		}
	}
}

void Arbiter::registerCharacterNewAction(Character* theCharacter)	//ask the character for a new action and store it
{
	//Action* newAction = theCharacter -> decideNextAction();
	std::cout << "[placeholder method] Now deciding next character action..." << std::endl;

}

void Arbiter::handleActiveAttacks(Character* theCharacter)			//charge character action and eventually perform the attack
{
	std::cout << "[placeholder method] Now handling attacks active attacks..." << std::endl;
}

void Arbiter::endCharacterTurn(Character* theCharacter)				//prepare character for turn end
{
	theCharacter -> incFatigue();
	m_characterHeap.updateTop();
}

//victory condition checking
void Arbiter::checkVictoryConditions()
{
	Game* gamePtr = Game::getInstance();

	if(!(gamePtr -> getTeam(Game::TeamEnum::LEFT) -> getTeamSize()))
		m_winningTeam = Game::TeamEnum::RIGHT;
	else if(!(gamePtr -> getTeam(Game::TeamEnum::RIGHT) -> getTeamSize()))
		m_winningTeam = Game::TeamEnum::LEFT;
}

void Arbiter::createNewAttackFromAction(Action* generatingAction)
{
	Attack* newAttack = new Attack(generatingAction);
	m_attackList.push_back(newAttack);
}

bool Arbiter::performTurnCycle()
{
	Game* gamePtr = Game::getInstance();

	//obtain next character to act
	Character* currCharToAct = nextCharacterToAct();
	//prepare character for turn
	prepareCharacterForTurn(currCharToAct);
	//evolve effect on character
	evolveEffectsOnCharacter(currCharToAct);
	//if character can act 
	if(currCharToAct -> canActThisTurn())
	{
		//if the character has an action to charge up
		if(currCharToAct -> isChargingAnAction())
			currCharToAct -> chargeAction();
		else	//otherwise it must be created and inserted in an attack
		{
			//obtain action from character
			Action* newAction = currCharToAct -> decideNextAction();

			//first check if the action targets another action: if so the attack already exists
			if(newAction -> getTarget() && typeid(newAction -> getTarget()) == typeid(Action*))			//perform check on TypeId first to soften RTTI performance penalty
				dynamic_cast<Action*>(newAction -> getTarget()) -> getAttack() -> addAnotherAction(newAction);	
			else	//otherwise it must be created from scratch
				createNewAttackFromAction(newAction);
		}
	}

	//character turn ends
	endCharacterTurn(currCharToAct);
	//check victory conditions
	checkVictoryConditions();

	//if no one won a new turn can happen
	return m_winningTeam == Game::TeamEnum::COUNT_TEAMS;
}

int Arbiter::getLegalTargetListForAction(Action* action, Targetable* targetVector[], int maxBufferSize = Action::MAX_TARGET_BUFFER_SIZE)
{
	int insertedElements = 0;

	if(insertedElements < maxBufferSize && action -> canTargetThis(g_TargetTypeEnum::ALLIED_CHARACTER))
	{
		Team::TeamCharacterList::Iterator iter = action -> getOwner() -> getTeam() -> getMembersIterator();
		Team::TeamCharacterList::Iterator endIter = iter.endIterator();

		for(; iter != endIter; ++iter)
			targetVector[insertedElements++] = dynamic_cast<Targetable*>(*(iter.current()));
	}
}