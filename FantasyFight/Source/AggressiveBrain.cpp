#include "AggressiveBrain.h"
#include "ActionLibraryRecord.h"
#include "Action.h"
#include "Character.h"
#include "Game.h"
#include "Arbiter.h"
#include "Team.h"

//TODO to be improved: detect BEST action to make
ActionLibraryRecord* AggressiveBrain::decideAction(Targetable* target)
{
	Game* instance = Game::getInstance();
	Arbiter* arbiter = instance -> getArbiter();
	Game::GameActionLibraryRecordList* actionLibrary = instance -> getActionLibraryRecordList();
	Game::GameActionLibraryRecordList::Iterator iter = actionLibrary -> begin();
	Game::GameActionLibraryRecordList::Iterator end = actionLibrary -> end();

	ActionLibraryRecord* ret = nullptr;

	//decide which target type to use
	g_TargetTypeEnum targetType;
	if(target < 0)
		targetType = g_TargetTypeEnum::NO_TARGET;
	else if(target == nullptr)
		targetType = g_TargetTypeEnum::TARGET_COUNT;
	else
	{
		targetType = target -> getTargetType();
		if(targetType == g_TargetTypeEnum::ANY_CHARACTER)
		{
			Character* targeted = (Character*) target;
			targetType = (targeted -> getTeam() == m_owner -> getTeam()) ? g_TargetTypeEnum::ALLIED_CHARACTER : g_TargetTypeEnum::ENEMY_CHARACTER;
		}
	}

	for(; iter != end; ++iter)
	{
		ret = *(iter.current());
		if
		(
			(ret -> canBePerformedByCharacter(m_owner))
			&&	(
					(targetType != g_TargetTypeEnum::TARGET_COUNT && ret -> canTargetThis(targetType)) 
				||	(targetType == g_TargetTypeEnum::TARGET_COUNT && arbiter -> getLegalTargetListForAction(ret, m_owner) > 0)
				)
		)
		{
			break;	//action found
		}
	}

	return ret;
}

Targetable* AggressiveBrain::decideTarget(ActionLibraryRecord* actionRecord)
{
	Targetable* ret = nullptr;

	if(actionRecord && !actionRecord -> canTargetThis(g_TargetTypeEnum::NO_TARGET))	//aciton needs a target
	{
		Arbiter::ArbiterTargetableList possibleTargets;
		if(Game::getInstance() -> getArbiter() -> getLegalTargetListForAction(actionRecord, m_owner, &possibleTargets))
		{
			ret = *(possibleTargets.begin().current());	//TODO improve: best target, not first
		}
	}
	else if(!actionRecord)	//action still to be decided
	{
		Team::TeamCharacterList::Iterator targetIter = m_owner -> getTeam() -> getEnemyTeam() -> getActiveMembersIterator();
		Team::TeamCharacterList::Iterator endIter = targetIter.endIterator();

		if(targetIter != endIter)
		{
			Character* target = *(targetIter.current());
			++targetIter;
		
			for(; targetIter != endIter; ++targetIter)
			{
				if(target -> getHP() < (**targetIter.current()).getHP())
					target = *targetIter.current();
			}

			ret = target;
		}
	}
	//otherwise action don't need any target

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
	MyString name;

	switch (ownerClass)
	{
	case WARRIOR:
		attribPrio[0] = g_AttributesEnum::STRENGTH;
		attribPrio[1] = g_AttributesEnum::DEXTERITY;
		attribPrio[2] = g_AttributesEnum::INTELLIGENCE;
		name = "AI Warrior";
		break;
	case THIEF:
		attribPrio[0] = g_AttributesEnum::DEXTERITY;
		attribPrio[1] = g_AttributesEnum::INTELLIGENCE;
		attribPrio[2] = g_AttributesEnum::STRENGTH;
		name = "AI Thief";
		break;
	case WIZARD:
		attribPrio[0] = g_AttributesEnum::INTELLIGENCE;
		attribPrio[1] = g_AttributesEnum::DEXTERITY;
		attribPrio[2] = g_AttributesEnum::STRENGTH;
		name = "AI Mage";
		break;
	default:
		return nullptr;
	}

	m_owner = new Character(name, this, ownerClass, attribPrio);
	return m_owner;
}