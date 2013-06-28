#include "AggressiveBrain.h"
#include "Action.h"
#include "ActionLibraryRecord.h"
#include "Targetable.h"

Brain* Brain::buildABrain()
{
	return new AggressiveBrain();
}

Action* Brain::buildNewActionForOwner()
{
	Action* ret = nullptr;

	ActionLibraryRecord* actionRecord = nullptr;
	Targetable* target = nullptr;

	while(!actionRecord || (!actionRecord -> canTargetThis(g_TargetTypeEnum::NO_TARGET) && !target))
	{
		actionRecord = decideAction();
		target = decideTarget(actionRecord);
	}

	return actionRecord ? actionRecord -> buildActionInstance(m_owner, target) : nullptr;
}