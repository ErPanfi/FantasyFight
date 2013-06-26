#ifndef FANTASYFIGHT_ATTACK_H
#define FANTASYFIGHT_ATTACK_H

#include "Team.h"
#include "List.h"

class Arbiter;
class Action;

class Attack
{
public:
	//action list typedef
	typedef List<Action*, Team::MAX_TEAM_SIZE> ActionList;
	friend class Arbiter;

private:
	//action list
	ActionList m_actionsList;
	unsigned int m_actionToChargeUp;


public:

	Attack(Action *firstAction);

	//action list management
	void addAnotherAction(Action* newAction);
	void removeActionFromList(Action* targetAction);
	ActionList::Iterator getActionIterator()	const { return m_actionsList.begin(); }	//TODO implement this with const_iterator: RO access to the list, while still accessing action methods
	inline Action* getGeneratingAction()		const { return *(m_actionsList.begin().current()); }
	//action charging
	void actionHasCharged(Action& actionCharged);
	unsigned int getActionToChargeNum()			const { return m_actionToChargeUp; }
};

#endif