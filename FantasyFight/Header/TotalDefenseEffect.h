#ifndef FANTASYFIGHT_EFFECT_TOTALDEFENSE_H
#define FANTASYFIGHT_EFFECT_TOTALDEFENSE_H

#include "ActiveEffect.h"

class TotalDefenseEffect : public ActiveEffect
{
private:
	int m_bonusApplied;

protected:
	virtual void applyEffectOnTarget();

public:

	TotalDefenseEffect(Character* owner);

	virtual void applyAssignmentEffect();
	virtual void applyDestructionEffect();
	virtual ActiveEffect* makeCopyOfThis(Targetable* newTarget);

	static const int DEFAULT_CHARGES = 1;
};

#endif
