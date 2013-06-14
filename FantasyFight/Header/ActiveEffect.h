#ifndef FANTASYFIGHT_ACTIVEEFFECT_H
#define FANTASYFIGHT_ACTIVEEFFECT_H

class Targetable;
class Character;

class ActiveEffect
{
private:

	unsigned int m_chargeCounter;

	Targetable*	m_target;
	Character* m_owner;

	virtual void applyEffectOnTarget() = 0;		//this is mandatory to implement, event empty

public:

	ActiveEffect(int charges, Character* owner, Targetable* target);

	virtual void applyAssignmentEffect();
	virtual void applyRecurringEffect();
	virtual void applyDestructionEffect();
	virtual bool canBeRemoved() const;
	virtual ActiveEffect* makeCopyOfThis() = 0;
};

#endif