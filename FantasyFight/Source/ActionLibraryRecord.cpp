#include "ActionLibraryRecord.h"

ActionLibraryRecord::ActionLibraryRecord(unsigned int baseChargingTime, const char desc[], unsigned int MPCost, Action::ActionBuilderMethod builderMethod)
	: m_baseChargingTime(baseChargingTime)
	, m_MPCost(MPCost)
	, m_builderMethod(builderMethod)
{
	m_description = new MyString(desc);
}