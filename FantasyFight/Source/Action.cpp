#include "Action.h"
#include "Printable.h"
#include "ActionLibraryRecord.h"

Action::Action(Character* owner, Targetable* target, unsigned int chargingTime, const ActionLibraryRecord* const actionRecord)
	: Targetable(actionRecord -> getName())
	, m_owner(owner)
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

Printable* Action::buildActionChargedPrintable() const
{
	return new Printable(m_name + " has charged. " + m_remainigChargingTime + " turns remaining.");
}

/*
MyString Action::getDescription() const
{ 
	return m_actionRecord -> getDescription(); 
}
*/