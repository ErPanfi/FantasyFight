#ifndef FANTASYFIGHT_MELEEATTACK_H
#define FANTASYFIGHT_MELEEATTACK_H

#include "Action.h"
#include "ActionLibraryRecord.h"


class MeleeAttack : public Action
{
private:
	class Registerer
	{
		Registerer();
	};

	static Registerer registerer;

	static ActionLibraryRecord* buildActionLibraryRecord();

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

	static const unsigned int DEFAULT_CHARGE_TIME = 1;
	static const unsigned int DEFAULT_MP_COST = 0;
	static const ActionLibraryRecord::RecordBitmask DEFAULT_TARGET_TYPE_MASK = 1 << g_TargetTypeEnum::ENEMY_CHARACTER;
	static const ActionLibraryRecord::RecordBitmask DEFAULT_CHARACTER_CLASS_MASK =	1 << g_CharacterClassEnum::THIEF	//all classes can perform this
																				 |	1 << g_CharacterClassEnum::WARRIOR
																				 |	1 << g_CharacterClassEnum::WIZARD;
	static const MyString DEFAULT_DESCRIPTION;
};

#endif