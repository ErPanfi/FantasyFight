#include "HumanBrain.h"
#include "Character.h"
#include "ActionLibraryRecord.h"
#include "Arbiter.h"

#include"IOManager.h"

HumanBrain::HumanBrain()
{
	resetActionBuilder();
}

Character* HumanBrain::buildOwner(g_CharacterClassEnum ownerClass)
{
	g_AttributesEnum attribPrio[G_PRIORITIZABLE_ATTRIBS];
	MyString name;

	switch (ownerClass)
	{
	case WARRIOR:
		attribPrio[0] = g_AttributesEnum::STR;
		attribPrio[1] = g_AttributesEnum::DEX;
		attribPrio[2] = g_AttributesEnum::INT;
		name = "Human Warrior";
		break;
	case THIEF:
		attribPrio[0] = g_AttributesEnum::DEX;
		attribPrio[1] = g_AttributesEnum::INT;
		attribPrio[2] = g_AttributesEnum::STR;
		name = "Human Thief";
		break;
	case WIZARD:
		attribPrio[0] = g_AttributesEnum::INT;
		attribPrio[1] = g_AttributesEnum::DEX;
		attribPrio[2] = g_AttributesEnum::STR;
		name = "Human mage";
		break;
	default:
		return nullptr;
	}

	m_owner = new Character(name, this, ownerClass, attribPrio);
	return m_owner;
}

Action* HumanBrain::buildNewActionForOwner()
{
	Action* ret = nullptr;

	//ask user first about the action to perform, then inquiry for the target
	if(!m_actionLibraryRecord)
	{
		decideAction();
	}
	else if(!m_target && !m_actionLibraryRecord -> canTargetThis(g_TargetTypeEnum::NO_TARGET))
	{
		decideTarget(m_actionLibraryRecord);
	}
	else
	{
		ret = m_actionLibraryRecord -> buildActionInstance(m_owner, m_target);
		resetActionBuilder();
	}

	return ret;
}

ActionLibraryRecord* HumanBrain::decideAction(Targetable* target)
{
	//target is surely nullptr
	Game* instance = Game::getInstance();
	Arbiter* arbiter = instance -> getArbiter();
	Game::GameActionLibraryRecordList* actionLibrary = instance -> getActionLibraryRecordList();
	Game::GameActionLibraryRecordList::Iterator iter = actionLibrary -> begin();
	Game::GameActionLibraryRecordList::Iterator end = actionLibrary -> end();

	Entity::EntityList actionList;

	for(; iter != end; ++iter)
	{
		ActionLibraryRecord* currAction = *iter.current();
		if(currAction -> canBePerformedByCharacter(m_owner) && arbiter -> getLegalTargetListForAction(currAction, m_owner) )
			actionList.push_back(currAction);
	}


	IOManager::instance().manageInput(actionList, (Entity**)(&m_actionLibraryRecord));

	return nullptr;	//this return is discarded
}

Targetable* HumanBrain::decideTarget(ActionLibraryRecord* actionLibraryRecord)
{
	if(actionLibraryRecord -> canTargetThis(g_TargetTypeEnum::NO_TARGET))	//action doesn't need a target
		return nullptr;

	Arbiter::ArbiterTargetableList targetList;

	Game::getInstance() -> getArbiter() -> getLegalTargetListForAction(actionLibraryRecord, m_owner, &targetList);
	Entity::EntityList entityTargetList;
	for(Arbiter::ArbiterTargetableList::Iterator iter = targetList.begin(); iter != targetList.end(); ++iter)
		entityTargetList.push_back(*iter.current());

	IOManager::instance().manageInput(entityTargetList, (Entity**)(&m_target));

	return nullptr;	//this return is discarded
}

