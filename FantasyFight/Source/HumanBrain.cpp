#include "HumanBrain.h"
#include "Character.h"
#include "ActionLibraryRecord.h"
#include "Arbiter.h"

#include"IOManager.h"

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

	ActionLibraryRecord* actionRecord = nullptr;
	Targetable* target = nullptr;

	//ask user first for the action, then for the target
	while(!actionRecord || (!actionRecord -> canTargetThis(g_TargetTypeEnum::NO_TARGET) && !target))
	{
		actionRecord = decideAction();
		target = decideTarget(actionRecord);
	}

	return actionRecord ? actionRecord -> buildActionInstance(m_owner, target) : nullptr;
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
		if(currAction -> canBePerformedByCharacter(m_owner))
			actionList.push_back(currAction);
	}

	Entity* ret = IOManager::instance().manageInput(actionList);

	return (ActionLibraryRecord*)ret;
}

Targetable* HumanBrain::decideTarget(ActionLibraryRecord* actionLibraryRecord)
{
	if(actionLibraryRecord -> canTargetThis(g_TargetTypeEnum::NO_TARGET))	//action doesn't need a target
		return nullptr;

	Arbiter::ArbiterTargetableList targetList;
	Entity* ret = nullptr;

	if(Game::getInstance() -> getArbiter() -> getLegalTargetListForAction(actionLibraryRecord, m_owner, &targetList) > 0)
	{

		Entity::EntityList actionList;
		for(Arbiter::ArbiterTargetableList::Iterator iter = targetList.begin(); iter != targetList.end(); ++iter)
			actionList.push_back(*iter.current());

		ret = IOManager::instance().manageInput(actionList);
	}

	return (Targetable*)ret;
}

