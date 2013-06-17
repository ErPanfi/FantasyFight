#include "ActionLibraryRecord.h"

ActionLibraryRecord::ActionLibraryRecord(unsigned int baseChargingTime, MyString &desc, unsigned int MPCost, Action::ActionBuilderMethod builderMethod)
	: m_baseChargingTime(baseChargingTime)
	, m_description(desc)
	, m_MPCost(MPCost)
	, m_builderMethod(builderMethod)
{
}