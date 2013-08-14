#include "TotalDefenseAction.h"
#include "CharacterClass.h"
#include "Game.h"
#include "TotalDefenseEffect.h"

//can be executed by all classes
const ActionLibraryRecord::RecordBitmask TotalDefenseAction::DEFAULT_CHARACTER_CLASS_MASK = CharacterClass::ALL_CLASSES_BITMASK;

//reference builder methods for further use
const Action::ActionBuilderMethod TotalDefenseAction::builderMethod = &TotalDefenseAction::Construct;

bool TotalDefenseAction::isActionSuccedeed()
{
	//no check is needed
	return true;
}

void TotalDefenseAction::applyEffectOnTarget()
{
	//decrementing fatigue by half increment now will made it greater by half increment at the end of the turn
	m_owner -> acquireNewEffect(new TotalDefenseEffect(m_owner));
}

Printable* TotalDefenseAction::buildFailurePrintable()
{
	//will never fail
	return nullptr;
}

TotalDefenseAction::TotalDefenseAction(Character* owner, const ActionLibraryRecord* const actionRecord)
	: Action(owner, owner, actionRecord -> getChargingTime(), actionRecord)	//target is owner
{}

ActionLibraryRecord* TotalDefenseAction::buildActionLibraryRecord()
{
	return new ActionLibraryRecord(DEFAULT_CHARGE_TIME, DEFAULT_MP_COST, DEFAULT_TARGET_TYPE_MASK, DEFAULT_CHARACTER_CLASS_MASK, "Total Defense", builderMethod);
}

Action* TotalDefenseAction::Construct(Character* owner, Targetable* target, const ActionLibraryRecord* const actionRecord)
{
	return new TotalDefenseAction(owner, actionRecord);
}

//autoregistering step
TotalDefenseAction::Registerer TotalDefenseAction::s_registerer;

TotalDefenseAction::Registerer::Registerer()
{
	Game::getInstance() -> addActionLibraryRecordToList(TotalDefenseAction::buildActionLibraryRecord());
}