#ifndef FANTASYFIGHT_TARGETABLE_H
#define FANTASYFIGHT_TARGETABLE_H

class Action;

class Targetable
{
public:
	virtual bool canBeTargetedByAction(Action* incomingAction) = 0;
};

#endif