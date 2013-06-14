#ifndef FANTASYFIGHT_TARGETABLE_H
#define FANTASYFIGHT_TARGETABLE_H

class Action;

class Targetable
{
public:

	enum TargetTypeEnum
	{
		ENEMY_CHARACTER,
		ALLIED_CHARACTER,
		NO_TARGET,
		TARGET_COUNT,
	};

	virtual bool canBeTargetedByAction(Action* incomingAction) = 0;
};

#endif