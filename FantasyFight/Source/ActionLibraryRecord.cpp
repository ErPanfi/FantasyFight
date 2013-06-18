#include "ActionLibraryRecord.h"
#include "Character.h"
#include "CharacterClass.h"

//default ctor
ActionLibraryRecord::ActionLibraryRecord()
	: m_baseChargingTime(0)
	, m_targetTypeAllowedMask(0)
	, m_MPCost(0)
	, m_classesAllowedMask(0)
	, m_description("NoDesc")
	, m_builderMethod(nullptr)
{}
//ctor with all members
ActionLibraryRecord::ActionLibraryRecord(
					unsigned int defaultCharge,
					unsigned int mpCost,
					unsigned char targetTypesMask, 
					unsigned char classesMask, 
					MyString desc, 
					Action::ActionBuilderMethod buildMethod
					)
					: m_baseChargingTime(defaultCharge)
					, m_MPCost(mpCost)
					, m_targetTypeAllowedMask(targetTypesMask)
					, m_classesAllowedMask(classesMask)
					, m_description(desc)
					, m_builderMethod(buildMethod)
{}

bool ActionLibraryRecord::canBePerformedByCharacter(Character* theCharacter)
{
	unsigned char mask = 1 << theCharacter -> getCharacterClass() -> getClassEnum();
	if((m_classesAllowedMask & mask ) == 0)
		return false;

	if(theCharacter -> getMP() < m_MPCost)
		return false;

	return true;
}
