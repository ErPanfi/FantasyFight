#include "AggressiveBrain.h"
#include "ActionLibraryRecord.h"
#include "Action.h"
#include "Character.h"
#include "Game.h"
#include "Arbiter.h"

//TODO to be improved
ActionLibraryRecord* AggressiveBrain::decideAction(Targetable* target)
{
	Game* instance = Game::getInstance();
	Arbiter* arbiter = instance -> getArbiter();
	Game::GameActionLibraryRecordList* actionLibrary = instance -> getActionLibraryRecordList();
	Game::GameActionLibraryRecordList::Iterator iter = actionLibrary -> begin();
	Game::GameActionLibraryRecordList::Iterator end = actionLibrary -> end();

	ActionLibraryRecord* ret = nullptr;

	for(; iter != end; ++iter)
	{
		ret = *(iter.current());
		if
		(
			(ret -> canBePerformedByCharacter(m_owner))
			&&	(
					(target && ret -> canTargetThis(target -> getTargetType())) 
				||	(!target && arbiter -> getLegalTargetListForAction(ret, m_owner) > 0)
				)
		)
		{
			break;	//action found
		}
	}

	return ret;
}

//TODO to be improved
Targetable* AggressiveBrain::decideTarget(ActionLibraryRecord* actionRecord)
{
	Targetable* ret = nullptr;
	if(actionRecord && !actionRecord -> canTargetThis(g_TargetTypeEnum::NO_TARGET))	//aciton needs a target
	{
		Arbiter::ArbiterTargetableList possibleTargets;
		if(Game::getInstance() -> getArbiter() -> getLegalTargetListForAction(actionRecord, m_owner, &possibleTargets))
		{
			ret = *(possibleTargets.begin().current());	
		}
	}
	else
	{
		//TODO perform global search on all possible targets, deciding what's the better one to interact with
	}

	return ret;
}


/*
Action* AggressiveBrain::buildNewActionForOwner()
{
	Game::GameActionLibraryRecordList* actionLibrary = Game::getInstance() -> getActionLibraryRecordList();
	Game::GameActionLibraryRecordList::Iterator iter = actionLibrary -> begin();
	Game::GameActionLibraryRecordList::Iterator end = actionLibrary -> end();

	ActionLibraryRecord* decidedAction = nullptr;

	//TODO implement intelligent action selection
	for(; iter != end; ++iter)
	{
		ActionLibraryRecord* currAction = *(iter.current());

	}

	Targetable* decidedTarget;

	Arbiter::ArbiterTargetableList possibleTargetList

	return decidedAction ? decidedAction -> buildActionInstance(m_owner
}
*/

Character* AggressiveBrain::buildOwner(g_CharacterClassEnum ownerClass)
{
	g_AttributesEnum attribPrio[G_PRIORITIZABLE_ATTRIBS];

	switch (ownerClass)
	{
	case WARRIOR:
		attribPrio[0] = g_AttributesEnum::STR;
		attribPrio[1] = g_AttributesEnum::DEX;
		attribPrio[2] = g_AttributesEnum::INT;
		break;
	case THIEF:
		attribPrio[0] = g_AttributesEnum::DEX;
		attribPrio[1] = g_AttributesEnum::INT;
		attribPrio[2] = g_AttributesEnum::STR;
		break;
	case WIZARD:
		attribPrio[0] = g_AttributesEnum::INT;
		attribPrio[1] = g_AttributesEnum::DEX;
		attribPrio[2] = g_AttributesEnum::STR;
		break;
	default:
		return nullptr;
	}

	m_owner = new Character(this, ownerClass, attribPrio);
	return m_owner;
}