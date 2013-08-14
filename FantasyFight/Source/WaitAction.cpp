#include "WaitAction.h"
#include "CharacterClass.h"
#include "Game.h"

//can be executed by all classes
const ActionLibraryRecord::RecordBitmask WaitAction::DEFAULT_CHARACTER_CLASS_MASK = CharacterClass::ALL_CLASSES_BITMASK;

//reference builder methods for further use
const Action::ActionBuilderMethod WaitAction::builderMethod = &WaitAction::Construct;

bool WaitAction::isActionSuccedeed()
{
	//no check is needed
	return true;
}

void WaitAction::applyEffectOnTarget()
{
	//decrementing fatigue by half increment now will made it greater by half increment at the end of the turn
	m_owner -> incFatigue(m_owner -> calcFatigueIncrement() / (-2));
}

Printable* WaitAction::buildFailurePrintable()
{
	//will never fail
	return nullptr;
}

WaitAction::WaitAction(Character* owner, const ActionLibraryRecord* const actionRecord)
	: Action(owner, owner, actionRecord -> getChargingTime(), actionRecord)	//target is owner
{}

ActionLibraryRecord* WaitAction::buildActionLibraryRecord()
{
	return new ActionLibraryRecord(DEFAULT_CHARGE_TIME, DEFAULT_MP_COST, DEFAULT_TARGET_TYPE_MASK, DEFAULT_CHARACTER_CLASS_MASK, "Wait", builderMethod);
}

Action* WaitAction::Construct(Character* owner, Targetable* target, const ActionLibraryRecord* const actionRecord)
{
	return new WaitAction(owner, actionRecord);
}

//autoregistering step
WaitAction::Registerer WaitAction::_registerer;

WaitAction::Registerer::Registerer()
{
	Game::getInstance() -> addActionLibraryRecordToList(WaitAction::buildActionLibraryRecord());
}