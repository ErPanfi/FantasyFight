#ifndef FANTASYFIGHT_MELEEATTACK_H
#define FANTASYFIGHT_MELEEATTACK_H

#include "Action.h"

class MeleeAttack : public Action
{

protected:
	int result;
	//ctor is protected: class can only be built through builder method
	MeleeAttack(Character* owner, Targetable* target, ActionLibraryRecord* actionRecord);

public:
	//base methods override 
	virtual bool isActionSuccedeed();
	virtual void applyEffectOnTarget();
	
	static Action* Construct(Character* owner, Targetable* target, ActionLibraryRecord* actionRecord);

	static const Action::ActionBuilderMethod builderMethod;
};

#endif