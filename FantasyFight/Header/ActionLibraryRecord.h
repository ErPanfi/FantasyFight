#ifndef FANTASYFIGHT_ACTIONLIBRARY_H
#define FANTASYFIGHT_ACTIONLIBRARY_H

#include "MyString.h"
#include "Action.h"
#include "Entity.h"

class Character;

class ActionLibraryRecord : public Entity
{
public:
	typedef unsigned char RecordBitmask;

private:
	//MyString			m_description;
	unsigned int		m_baseChargingTime;
	unsigned int		m_MPCost;
	RecordBitmask		m_classesAllowedMask;
	RecordBitmask		m_targetTypeAllowedMask;
	Action::ActionBuilderMethod m_builderMethod;

public:
	//default ctor
	ActionLibraryRecord();
	//ctor with all members
	ActionLibraryRecord(unsigned int defaultCharge,
						unsigned int mpCost,
						RecordBitmask targetTypesMask, 
						RecordBitmask classesMask, 
						MyString desc, 
						Action::ActionBuilderMethod buildMethod
						);

	virtual bool canBePerformedByCharacter(Character* theCharacter);
	virtual bool canTargetThis(Targetable* target) const;
	virtual bool canTargetThis(g_TargetTypeEnum targetType) const;

	unsigned int getChargingTime() const { return m_baseChargingTime; }

	//MyString getDescription() const { return m_description; }

	Action* buildActionInstance(Character* owner, Targetable* target) const;

	//entity inherited method
	virtual Printable* printEntity() const;


};

#endif