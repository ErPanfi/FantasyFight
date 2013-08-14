#include "TotalDefenseEffect.h"
#include "Character.h"
#include "IOManager.h"

TotalDefenseEffect::TotalDefenseEffect(Character* owner)
	: ActiveEffect(DEFAULT_CHARGES, owner, (Targetable*) owner)
{}

void TotalDefenseEffect::applyEffectOnTarget()
{}

void TotalDefenseEffect::applyAssignmentEffect()
{
	m_bonusApplied = m_owner -> getAttribModifier(g_AttributesEnum::DEXTERITY);	//todo include armor bonus
	m_owner -> m_attributes[g_AttributesEnum::DEFENCE] += m_bonusApplied;

	IOManager::instance().manageOutput(m_owner -> getName() + " defense successfully increased by " + m_bonusApplied);
}

void TotalDefenseEffect::applyDestructionEffect()
{
	m_owner -> m_attributes[g_AttributesEnum::DEFENCE] -= m_bonusApplied;

	IOManager::instance().manageOutput(m_owner -> getName() + " defense has decreased by " + m_bonusApplied);

	m_bonusApplied = 0;
}

ActiveEffect* TotalDefenseEffect::makeCopyOfThis(Targetable* newTarget)
{
	TotalDefenseEffect* ret = new TotalDefenseEffect(*this);

	ret -> m_target = newTarget;
	ret -> m_owner = (Character*) newTarget;

	return ret;
}