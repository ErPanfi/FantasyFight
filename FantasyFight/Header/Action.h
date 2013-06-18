#ifndef FANTASYFIGHT_ACTION_H
#define FANTASYFIGHT_ACTION_H

#include "Attack.h"
#include "Targetable.h"
#include "Global.h"
#include "MyString.h"

class Character;
class ActionLibraryRecord;

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

protected:

	Action(Character* owner);

public:

	//owner is RO
	Character* getOwner() const { return m_owner; }

	//attack handling: read only
	Attack* getAttack() const	{ return m_attack; }
	//charging time handling: RO
	unsigned int getRemainingChargingTime() const { return m_remainigChargingTime; }


	//target handling
	inline Targetable* getTarget() const { return m_target; }
	virtual bool canTargetThis(Targetable* target) const;
	virtual bool canTargetThis(g_TargetTypeEnum targetType) const;
	virtual bool canBeTargetedByAction(Action* incomingAction) {return incomingAction -> canTargetThis(m_target); }
	virtual inline g_TargetTypeEnum getTargetType() { return g_TargetTypeEnum::NO_TARGET; }	//default behaviour
	//max buffer size
	static const unsigned int MAX_TARGET_BUFFER_SIZE = 50;

	//action resolution methods
	virtual bool isActionSuccedeed() = 0;
	virtual void applyEffectOnTarget() = 0;

	//action factory management

	typedef Action* (*ActionBuilderMethod)(Character* owner, Targetable* target, ActionLibraryRecord actionRecord);

	//TODO in each action a registration step must be performed to the action library in class Game
	//TODO each action should have a static builder method, to be enclosed in ActionLibraryRecord... Like this
	//static virtual Action* buildActionInstance(Character* owner, Targetable* target, ActionLibraryRecord actionRecord) = 0;
};

#endif