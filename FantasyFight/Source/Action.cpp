#include "Action.h"

void Action::chargeUp()
{
	if(m_remainigChargingTime)
		m_remainigChargingTime--;
	if(!m_remainigChargingTime)
		m_attack -> actionHasCharged(this);
}

bool Action::canTargetThis(Targetable* target) const
{ 
	return canTargetThis(target -> getTargetType());
}

bool Action::canTargetThis(g_TargetTypeEnum targetType) const 
{ 
	return 
		(m_allowedTargetTypes && (m_allowedTargetTypes & (1 << targetType)) != 0)	//the mask contains something
	||	(!m_allowedTargetTypes && targetType == g_TargetTypeEnum::NO_TARGET);		//an empty mask (shouldn't happen) must be treated as no_target

}
