#ifndef FANTASYFIGHT_ACTION_H
#define FANTASYFIGHT_ACTION_H

#include "Attack.h"
#include "Targetable.h"
#include "Global.h"

class Character;

class Action : public Targetable
{
private:
	//owner
	Character* m_owner;

	//attack referral management: only an attack can claim this action
	Attack* m_attack;
	friend void Attack::addAnotherAction(Action* newAction);
	void setAttack(Attack* newValue) { m_attack = newValue; }

	//charging time management: only the owning character can charge up this action
	unsigned int m_remainigChargingTime;
	friend void Character::chargeAction();
	void chargeUp();

	//target of action, can be null
	Targetable* m_target;

	//list of allowed target types
	unsigned char m_allowedTargetTypes;

public:

	Action(Character* owner);

	//owner is RO
	Character* getOwner() const { return m_owner; }

	//attack handling: read only
	Attack* getAttack() const	{ return m_attack; }
	//charging time handling: RO
	unsigned int getRemainingChargingTime() const { return m_remainigChargingTime; }

	virtual bool canBeTargetedByAction(Action* incomingAction);
	virtual void applyEffectOnTarget() = 0;

	//target handling
	inline Targetable* getTarget() const { return m_target; }
	bool canTargetThis(Targetable* target) const;
	bool canTargetThis(g_TargetTypeEnum targetType) const;
	virtual inline g_TargetTypeEnum getTargetType() { return g_TargetTypeEnum::NO_TARGET; }	//default behaviour
	//max buffer size
	static const unsigned int MAX_TARGET_BUFFER_SIZE = 50;
};

#endif