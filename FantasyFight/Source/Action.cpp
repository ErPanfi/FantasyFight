#include "Action.h"

Action::Action(Character* owner, Targetable* target, unsigned int chargingTime, ActionLibraryRecord* actionRecord)
	: m_owner(owner)
	, m_target(target)
	, m_remainigChargingTime(chargingTime)
	, m_actionRecord(actionRecord)
{
}

void Action::chargeUp()
{
	if(m_remainigChargingTime)
		m_remainigChargingTime--;
	if(!m_remainigChargingTime)
		m_attack -> actionHasCharged(*this);
}