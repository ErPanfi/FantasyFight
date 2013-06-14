#include "Action.h"

void Action::chargeUp()
{
	if(m_remainigChargingTime)
		m_remainigChargingTime--;
	if(!m_remainigChargingTime)
		m_attack -> actionHasCharged(this);
}