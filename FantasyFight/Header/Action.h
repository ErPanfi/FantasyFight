#ifndef FANTASYFIGHT_ACTION_H
#define FANTASYFIGHT_ACTION_H

#include "Attack.h"
#include "Targetable.h"
#include "Global.h"
#include "MyString.h"
#include "Character.h"

class ActionLibraryRecord;

class Action : public Targetable
{

protected:
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

	//reference to generating action record
	ActionLibraryRecord* m_actionRecord;

	Action(Character* owner, Targetable* target, unsigned int chargingTime, ActionLibraryRecord* actionRecord);

public:

	//owner is RO
	Character* getOwner() const { return m_owner; }

	//attack handling: read only
	Attack* getAttack() const	{ return m_attack; }
	//charging time handling: RO
	unsigned int getRemainingChargingTime() const { return m_remainigChargingTime; }


	//target handling
	inline Targetable* getTarget() const { return m_target; }
	virtual bool canBeTargetedByAction(Action* incomingAction) { return false;}
	virtual inline g_TargetTypeEnum getTargetType() const { return g_TargetTypeEnum::NO_TARGET; }	//default behaviour, should be redefined in combined actions
	//max buffer size
	static const unsigned int MAX_TARGET_BUFFER_SIZE = 50;

	//action resolution methods
	virtual bool isActionSuccedeed() = 0;
	virtual void applyEffectOnTarget() = 0;

	//action factory management

	typedef Action* (*ActionBuilderMethod)(Character* owner, Targetable* target, ActionLibraryRecord* actionRecord);

	//TODO in each action a registration step must be performed to the action library in class Game
	//TODO each action should have a static builder method, to be enclosed in ActionLibraryRecord... Like this
	//static virtual Action* buildActionInstance(Character* owner, Targetable* target, ActionLibraryRecord actionRecord) = 0;
};

#endif