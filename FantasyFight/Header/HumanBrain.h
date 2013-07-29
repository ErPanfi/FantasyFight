#ifndef FANTASYFIGHT_HUMANBRAIN_H
#define FANTASYFIGHT_HUMANBRAIN_H

#include "Brain.h"

class HumanBrain : public Brain
{
protected:
	virtual ActionLibraryRecord* decideAction(Targetable* target = nullptr);
	virtual Targetable* decideTarget(ActionLibraryRecord* actionRecord = nullptr);

public:
	//action deciding
	virtual Action* buildNewActionForOwner() final;

	//create a new Character and become its brain
	virtual Character* buildOwner(g_CharacterClassEnum ownerClass);
};

#endif