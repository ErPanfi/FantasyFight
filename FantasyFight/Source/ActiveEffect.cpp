#include "ActiveEffect.h"
#include "Character.h"
#include "Targetable.h"

ActiveEffect::ActiveEffect(int charges, Character* owner, Targetable* target)
	: m_chargeCounter(charges)
	, m_owner(owner)
	, m_target(target)
{
}

void ActiveEffect::applyRecurringEffect()
{
	applyEffectOnTarget();
	m_chargeCounter--;
}

bool ActiveEffect::canBeRemoved() const
{
	return !m_chargeCounter;
}

void ActiveEffect::applyAssignmentEffect()
{
}

void ActiveEffect::applyDestructionEffect()
{
}
