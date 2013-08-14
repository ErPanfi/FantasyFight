#ifndef FANTASYFIGHT_EFFECT_ACTIVEEFFECT_H
#define FANTASYFIGHT_EFFECT_ACTIVEEFFECT_H

class Character;
class Targetable;


class ActiveEffect
{
protected:

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
	virtual ActiveEffect* makeCopyOfThis(Targetable* newTarget) = 0;

	Targetable* getTarget() const { return m_target; }
	Character* getOwner() const { return m_owner; }
};

#endif