#include "MeleeAttack.h"
#include "Game.h"
#include "Arbiter.h"
#include "CharacterClass.h"

//autoregistering step
MeleeAttack::Registerer MeleeAttack::registerer;
const ActionLibraryRecord::RecordBitmask MeleeAttack::DEFAULT_CHARACTER_CLASS_MASK = CharacterClass::ALL_CLASSES_BITMASK;

MeleeAttack::Registerer::Registerer()
{
	Game::getInstance() -> addActionLibraryRecordToList(MeleeAttack::buildActionLibraryRecord());
}

ActionLibraryRecord* MeleeAttack::buildActionLibraryRecord()
{
	MyString desc("Attacco in mischia");
	return new ActionLibraryRecord(DEFAULT_CHARGE_TIME, DEFAULT_MP_COST, DEFAULT_TARGET_TYPE_MASK, DEFAULT_CHARACTER_CLASS_MASK, desc, builderMethod);
}

//melee attack class
const Action::ActionBuilderMethod MeleeAttack::builderMethod = MeleeAttack::Construct;

MeleeAttack::MeleeAttack(Character* owner, Targetable* target, const ActionLibraryRecord* const actionRecord)
	: Action(owner, target, actionRecord -> getChargingTime(), actionRecord )
{
}

bool MeleeAttack::isActionSuccedeed()
{
	Character* target = dynamic_cast<Character*>(getTarget());
	result = Game::getInstance() -> getArbiter() -> performContest(getOwner(), g_AttributesEnum::MELEE_ACC, target, g_AttributesEnum::DEF);

	return result > 0;
}

void MeleeAttack::applyEffectOnTarget()
{
	if(result > 0)
	{
		dynamic_cast<Character*>(getTarget()) -> receiveDamage(result);
	}
}

Action* MeleeAttack::Construct(Character* owner, Targetable* target, const ActionLibraryRecord* const actionRecord)
{
	return new MeleeAttack(owner, target, actionRecord);
}


