#ifndef FANTASYFIGHT_ACTION_H
#define FANTASYFIGHT_ACTION_H

#include "Attack.h"
#include "Targetable.h"

class Character;

class Action : public Targetable
{
private:
	Character* m_owner;

	//attack referral management: only an attack can claim this action
	Attack* m_attack;
	friend void Attack::addAnotherAction(Action* newAction);
	void setAttack(Attack* newValue) { m_attack = newValue; }

	//charging time management: only the owning character can charge up this action
	unsigned int m_remainigChargingTime;
	friend void Character::chargeAction();
	void chargeUp();

	Targetable* target;


public:
	
	Action(Character* owner);

	//attack handling: read only
	Attack* getAttack() const	{ return m_attack; }
	//charging time handling: RO
	unsigned int getRemainingChargingTime() const { return m_remainigChargingTime; }

	virtual bool canBeTargetedByAction(Action* incomingAction);
	virtual void applyEffectOnTarget() = 0;
};

#endif