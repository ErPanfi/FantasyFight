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

	virtual void applyEffectOnTarget() = 0;

public:

	ActiveEffect(int charges, Character* owner, Targetable* target);

	virtual void applyRecurringEffect();
	virtual bool canBeRemoved() const;
	virtual ActiveEffect* makeCopyOfThis() = 0;
};

#endif