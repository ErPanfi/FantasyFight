#include "MeleeAttack.h"
#include "Game.h"
#include "Arbiter.h"
#include "ActionLibraryRecord.h"

const Action::ActionBuilderMethod MeleeAttack::builderMethod = MeleeAttack::Construct;

MeleeAttack::MeleeAttack(Character* owner, Targetable* target, ActionLibraryRecord* actionRecord)
	: Action(owner, target, actionRecord -> getChargingTime() )
{
}

bool MeleeAttack::isActionSuccedeed()
{
	assert(typeid(getTarget()) == typeid(Character *));
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

Action* MeleeAttack::Construct(Character* owner, Targetable* target, ActionLibraryRecord* actionRecord)
{
	return new MeleeAttack(owner, target, actionRecord);
}


