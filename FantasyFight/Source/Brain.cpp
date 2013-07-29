#include "AggressiveBrain.h"
#include "HumanBrain.h"
#include "Action.h"
#include "ActionLibraryRecord.h"
#include "Targetable.h"

Brain* Brain::buildABrain(bool humanBrain)
{
	if(humanBrain)
		return new HumanBrain();
	else
		return new AggressiveBrain();
}

Action* Brain::buildNewActionForOwner()
{
	Action* ret = nullptr;

	ActionLibraryRecord* actionRecord = nullptr;
	Targetable* target = nullptr;

	//select first the target, then the action
	while(!actionRecord || (!actionRecord -> canTargetThis(g_TargetTypeEnum::NO_TARGET) && !target))
	{
		target = decideTarget();
		actionRecord = decideAction(target);
	}

	return actionRecord ? actionRecord -> buildActionInstance(m_owner, target) : nullptr;
}