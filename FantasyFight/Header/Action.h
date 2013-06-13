#ifndef FANTASYFIGHT_ACTION_H
#define FANTASYFIGHT_ACTION_H

#include "Attack.h"
#include "Targetable.h"

class Character;

class Action : public Targetable
{
private:
	Character* m_owner;

	//attack management
	Attack* m_attack;
	friend void Attack::addAnotherAction(Action* newAction);
	void setAttack(Attack* newValue) { m_attack = newValue; }

	unsigned int m_remainigChargingTime;

	Targetable* target;


public:
	
	Action(Character* owner);

	//attack handling: read only
	Attack* getAttack() const	{ return m_attack; }
	//charging time handling: RO
	unsigned int getRemainingChargingTime() const { return m_remainigChargingTime; }

	virtual bool canBeTargetedByAction(Action* incomingAction);
	void applyEffectOnTarget();
};

#endif