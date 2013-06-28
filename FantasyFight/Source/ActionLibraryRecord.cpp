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
	RecordBitmask mask = 1 << (theCharacter -> getCharacterClass() -> getClassEnum());
	if((m_classesAllowedMask & mask ) == 0)
		return false;

	if(theCharacter -> getMP() < m_MPCost)
		return false;

	return true;
}

bool ActionLibraryRecord::canTargetThis(Targetable* target) const
{ 
	return canTargetThis(target -> getTargetType());
}

bool ActionLibraryRecord::canTargetThis(g_TargetTypeEnum targetType) const 
{ 
	assert(targetType < g_TargetTypeEnum::TARGET_COUNT);
	
	RecordBitmask targetMask;

	switch (targetType)
	{
	case ANY_CHARACTER:
		targetMask = (1 << g_TargetTypeEnum::ENEMY_CHARACTER) | (1 << g_TargetTypeEnum::ALLIED_CHARACTER);
		break;

	default:
		targetMask = (1 << targetType);
		break;
	}

	return targetMask == (m_targetTypeAllowedMask & targetMask);
}

Action* ActionLibraryRecord::buildActionInstance(Character* owner, Targetable* target) const
{
	return m_builderMethod(owner, target, this);
}

