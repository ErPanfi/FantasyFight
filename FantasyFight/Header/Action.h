#ifndef FANTASYFIGHT_ACTION_H
#define FANTASYFIGHT_ACTION_H

#include "Attack.h"
#include "Targetable.h"
#include "Global.h"
#include "MyString.h"

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
	bool canTargetThis(Targetable* target) const;
	bool canTargetThis(g_TargetTypeEnum targetType) const;
	virtual bool canBeTargetedByAction(Action* incomingAction) {return incomingAction -> canTargetThis(m_target); }
	virtual inline g_TargetTypeEnum getTargetType() { return g_TargetTypeEnum::NO_TARGET; }	//default behaviour
	//max buffer size
	static const unsigned int MAX_TARGET_BUFFER_SIZE = 50;

	//action resolution methods
	virtual bool isActionSuccedeed() const = 0;
	virtual void applyEffectOnTarget() = 0;

	//action factory management

	typedef Action* (*ActionBuilderMethod)(Character* owner, Targetable* target);
	virtual Action* buildActionInstance(Character* owner, Targetable* target) = 0;

	struct ActionLibraryRecord
	{
		unsigned int defaultChargingTime;
		unsigned char targetTypeAllowedMask;
		unsigned char classesAllowedMask;
		MyString description;
		ActionBuilderMethod builderMethod;

		//default ctor
		ActionLibraryRecord()
			: defaultChargingTime(0)
			, targetTypeAllowedMask(0)
			, classesAllowedMask(0)
			, description("NoDesc")
			, builderMethod(nullptr)
		{}
		//ctor with all members
		ActionLibraryRecord(unsigned int defaultCharge,
							unsigned char targetTypesMask, 
							unsigned char classesMask, 
							MyString desc, 
							ActionBuilderMethod buildMethod
							)
							: defaultChargingTime(defaultCharge)
							, targetTypeAllowedMask(targetTypesMask)
							, classesAllowedMask(classesMask)
							, description(desc)
							, builderMethod(buildMethod)
		{}


	};

	//TODO in each action a registeration step must be performed
};

#endif