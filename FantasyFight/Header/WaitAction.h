#ifndef FANTASYFIGHT_ACTION_WAITACTION_H
#define FANTASYFIGHT_ACTION_WAITACTION_H

#include "Action.h"
#include "ActionLibraryRecord.h"

class WaitAction: public Action
{
private:
	class Registerer
	{
	public: 
		Registerer();
	};

	static Registerer s_registerer;

	static ActionLibraryRecord* buildActionLibraryRecord();

protected:

	//use builder method pointer to call this
	WaitAction(Character* owner, const ActionLibraryRecord* const actionRecord);

public:
	//base methods override 
	virtual bool isActionSuccedeed();
	virtual void applyEffectOnTarget();
	virtual Printable* buildFailurePrintable();
	
	static Action* Construct(Character* owner, Targetable* target, const ActionLibraryRecord* const actionRecord);

	static const Action::ActionBuilderMethod builderMethod;

	static const unsigned int DEFAULT_CHARGE_TIME = 1;
	static const unsigned int DEFAULT_MP_COST = 0;
	static const ActionLibraryRecord::RecordBitmask DEFAULT_TARGET_TYPE_MASK = 1 << g_TargetTypeEnum::NO_TARGET;
	static const ActionLibraryRecord::RecordBitmask DEFAULT_CHARACTER_CLASS_MASK;
};

#endif