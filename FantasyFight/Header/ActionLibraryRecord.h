#ifndef FANTASYFIGHT_ACTIONLIBRARY_H
#define FANTASYFIGHT_ACTIONLIBRARY_H

#include "MyString.h"
#include "Action.h"

class ActionLibraryRecord
{

private:
	MyString			m_description;
	unsigned int		m_baseChargingTime;
	unsigned int		m_MPCost;
	unsigned char		m_classRequirements;
	Action::ActionBuilderMethod m_builderMethod;

public:
	ActionLibraryRecord(unsigned int baseChargingTime, MyString &desc, unsigned int baseCost, Action::ActionBuilderMethod  builderMethod);


};

#endif