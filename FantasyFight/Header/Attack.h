#ifndef FANTASYFIGHT_ATTACK_H
#define FANTASYFIGHT_ATTACK_H

class Action;

class Attack
{
private:
	
	int m_actionToChargeUp;

public:

	Attack(Action *firstAction);

	void addAnotherAction(Action* newAction);
	void removeAction(Action* actionToDelete);	
	void actionHasCharged(Action* actionCharged);
}

#endif