#ifndef FANTASYFIGHT_ATTACK_H
#define FANTASYFIGHT_ATTACK_H

#include "Team.h"
class Action;

class Attack
{
private:
	
	int m_actionToChargeUp;
	Action* nActions[Team::MAX_TEAM_SIZE];
public:

	Attack(Action *firstAction);

	void addAnotherAction(Action* newAction);
	void removeAction(Action* actionToDelete);	
	void actionHasCharged(Action* actionCharged);
};

#endif