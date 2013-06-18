#ifndef FANTASYFIGHT_ACTIONLIBRARY_H
#define FANTASYFIGHT_ACTIONLIBRARY_H

#include "MyString.h"
#include "Action.h"

class Character;

class ActionLibraryRecord
{

private:
	MyString			m_description;
	unsigned int		m_baseChargingTime;
	unsigned int		m_MPCost;
	unsigned char		m_classesAllowedMask;
	unsigned char		m_targetTypeAllowedMask;
	Action::ActionBuilderMethod m_builderMethod;

public:
	ActionLibraryRecord(unsigned int baseChargingTime, const char desc[], unsigned int baseCost, Action::ActionBuilderMethod  builderMethod);

	//default ctor
	ActionLibraryRecord();
	//ctor with all members
	ActionLibraryRecord(unsigned int defaultCharge,
						unsigned int mpCost,
						unsigned char targetTypesMask, 
						unsigned char classesMask, 
						MyString desc, 
						Action::ActionBuilderMethod buildMethod
						);

	virtual bool canBePerformedByCharacter(Character* theCharacter);

	unsigned int getChargingTime() const { return m_baseChargingTime; }
};

#endif