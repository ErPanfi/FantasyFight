#include "Attack.h"
#include "Action.h"

Attack::Attack(Action *firstAction) 
	: m_actionToChargeUp(0)
{
	addAnotherAction(firstAction);	//calling this for code reusability... and because it has higher permissions on class Action ;-)
}

void Attack::addAnotherAction(Action* newAction)	//this is friend of class Action
{
	if(newAction && (!m_actionsList.size() || getGeneratingAction() -> canBeTargetedByAction(newAction)))
	{
		m_actionsList.push_back(newAction);
		newAction -> m_attack = this;				//editor mark m_attack as inaccessible...Fool. ;-P
		if(newAction -> getRemainingChargingTime())
			m_actionToChargeUp++;
	}
}

void Attack::removeActionFromList(Action* targetAction)
{
	if(targetAction)
	{
		ActionList::Iterator iter = m_actionsList.find(&targetAction);
		if(iter != m_actionsList.end())
		{
			iter.remove();
			if(targetAction -> getRemainingChargingTime())
				m_actionToChargeUp--;
		}
	}
}

void Attack::actionHasCharged(Action* targetAction)
{
	if(targetAction && m_actionsList.find(&targetAction) != m_actionsList.end())
	{
		m_actionToChargeUp--;
	}
}